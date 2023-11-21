#include "Server.hpp"

#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h> // inet_ntop

#include <iostream>

#define IRC_ASSERT_THROW(COND, MSG) do { if (COND) { throw std::runtime_error(MSG); }} while(0);

static int create_listening_socket(struct addrinfo const* address)
{
    int listener = socket(address->ai_family, address->ai_socktype, address->ai_protocol);

    if (listener >= 0)
    {
        // Remove "address already in use" error message
        int option_value = true;
        if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(option_value)) < 0
            || bind(listener, address->ai_addr, address->ai_addrlen) < 0
            || listen(listener, 10) < 0)
        {
            close(listener);
            return -1;
        }
    }

    return listener;
}

Server::Server()
{
    struct addrinfo hints = {};
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags    = AI_PASSIVE;

    struct addrinfo *address_list = NULL;

    int error = getaddrinfo(NULL, "6667", &hints, &address_list);

    IRC_ASSERT_THROW(error != 0, gai_strerror(error));

    struct addrinfo* ipv6 = NULL;
    struct addrinfo* ipv4 = NULL;

    for(struct addrinfo* it = address_list; it != NULL; it = it->ai_next)
    {
        if (ipv4 == NULL && it->ai_family == AF_INET)
        {
            ipv4 = it;
        }
        else if (ipv6 == NULL && it->ai_family == AF_INET6)
        {
            ipv6 = it;
        }
    }

    Socket listener = {};
    listener.fd = -1;
    listener.events = POLLIN;

    if (ipv6 != NULL)
    {
        listener.fd = create_listening_socket(ipv6);

        if (listener.fd < 0)
        {
            std::cerr << "IPv6 listening socket creation failure: " << std::strerror(errno) << '\n';
        }
    }
    if (ipv4 != NULL && listener.fd < 0)
    {
        listener.fd = create_listening_socket(ipv4);

        if (listener.fd < 0)
        {
            std::cerr << "IPv4 listening socket creation failure: " << std::strerror(errno) << '\n';
        }
    }

    freeaddrinfo(address_list);

    IRC_ASSERT_THROW(listener.fd < 0, "No listening socket could be created.\n");

    m_socket_list.push_back(listener);
}

Server::~Server()
{
    for (std::vector<Socket>::iterator socket = m_socket_list.begin(); socket != m_socket_list.end(); ++socket)
    {
        if (socket->fd != -1)
        {
            close(socket->fd);
            socket->fd = -1;
            socket->events = 0;
            socket->revents = 0;
        }
    }
}

void Server::run()
{
    while(1)
    {
        int poll_count = poll(m_socket_list.data(), m_socket_list.size(), -1);

        if (poll_count == -1) { perror("poll"); }

        // Handle client events

        for(std::vector<Socket>::iterator client = m_socket_list.begin() + 1; client != m_socket_list.end(); ++client)
        {
            if (client->revents & POLLIN)
            {
                // Should be stored for each socket to handle messages not coming in whole
                char socket_stream[512] = {};

                int read_bytes = recv(client->fd, socket_stream, sizeof(socket_stream), 0);

                if (read_bytes < 0)
                {
                    perror("recv:");
                }
                else if (read_bytes == 0)
                {
                    close(client->fd);
                    std::swap(*client, m_socket_list.back());
                    m_socket_list.pop_back();
                }
                else
                {
                    for(std::vector<Socket>::iterator destination = m_socket_list.begin() + 1; destination != m_socket_list.end(); ++destination)
                    {
                        if (destination->fd == client->fd || (destination->revents & POLLOUT) == 0)
                        {
                            continue;
                        }
                        if (send(destination->fd, socket_stream, read_bytes, 0) == -1)
                        {
                            perror("send:");
                        }
                    }
                }
            }
        }
        
        Socket& listener = m_socket_list.front();

        if (listener.revents & POLLIN)
        {
            struct sockaddr_storage address;
            socklen_t address_size = sizeof(address);
            
            Socket client = {};
            client.fd = accept(listener.fd, (struct sockaddr *)&address, &address_size);
            client.events = POLLIN | POLLOUT;

            if (client.fd == -1)
            {
                std::perror("accept");
            }
            else
            {
                m_socket_list.push_back(client);

                char buf[INET6_ADDRSTRLEN];

                void *ip;

                if (address.ss_family == AF_INET)
                {
                    ip = &(((struct sockaddr_in *)(&address))->sin_addr);
                }
                else
                {
                    ip = &(((struct sockaddr_in6 *)(&address))->sin6_addr);
                }

                printf("pollserver: new connection from %s on socket %d\n",
                    inet_ntop(address.ss_family, ip, buf, INET6_ADDRSTRLEN), client.fd);
            }
        }
    }
}
