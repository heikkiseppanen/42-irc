#include "Server.hpp"

#include <netdb.h>
#include <unistd.h>

#include <iostream>

#define IRC_ASSERT_THROW(COND, MSG) do { if (COND) { throw std::runtime_error(MSG); }} while(0);

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

    struct addrinfo* ipv4 = NULL;
    struct addrinfo* ipv6 = NULL;

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

    IRC_ASSERT_THROW(ipv4 == NULL && ipv6 == NULL, "No IPv4 or IPv6 supported socket found");

    struct addrinfo address = (ipv6 != NULL) ? *ipv6 : *ipv4;

    freeaddrinfo(address_list);

    Socket listener = {};

    listener.fd = socket(address.ai_family, address.ai_socktype, address.ai_protocol);
    listener.events = POLLIN;

    IRC_ASSERT_THROW(listener.fd < 0, std::strerror(errno));

    // Remove "address already in use" error message

    int option_value = true;
    setsockopt(listener.fd, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(option_value));

    IRC_ASSERT_THROW(bind(listener.fd, address.ai_addr, address.ai_addrlen) < 0, std::strerror(errno));

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
                    perror("recv");
                }
                else if (read_bytes == 0)
                {
                    printf("socket %d hung up\n", client->fd);
                    close(client->fd); // Bye!
                    std::swap(*client, m_socket_list.back());
                    m_socket_list.pop_back();
                }
                else
                {
                    for(std::vector<Socket>::iterator destination = m_socket_list.begin() + 1; destination != m_socket_list.end(); ++destination)
                    {
                        if (destination->fd == client->fd)
                        {
                            if (send(destination->fd, socket_stream, read_bytes, 0) == -1)
                            {
                                perror("send");
                            }
                        }
                    }
                }
            }
        }
        
        Socket& listener = m_socket_list.front();

        if (listener.revents & POLLIN)
        {
            struct sockaddr_storage address; // Client address
            socklen_t address_size = sizeof(address);
            // If listener is ready to read, handle new connection
            
            Socket client = {};
            client.fd = accept(listener.fd, (struct sockaddr *)&address, &address_size);

            if (client.fd == -1)
            {
                std::perror("accept");
            }
            else
            {
                m_socket_list.push_back(client);

                printf("pollserver: new connection from %s on "
                    "socket %d\n",
                    inet_ntop(remoteaddr.ss_family,
                        get_in_addr((struct sockaddr*)&remoteaddr),
                        remoteIP, INET6_ADDRSTRLEN),
                    newfd);
            }
        }
    }
}
