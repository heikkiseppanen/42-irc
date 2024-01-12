#include "Socket.hpp"

#include "Debug.hpp"

#include <string>
#include <netdb.h>
#include <fcntl.h>

static int create_listener_socket(struct addrinfo const* address)
{
    int listener = socket(address->ai_family, address->ai_socktype, address->ai_protocol);

    fcntl(listener, F_SETFL, O_NONBLOCK);

    if (listener >= 0)
    {
        // Remove "address already in use" error message
        int reuse_address = true;
        if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &reuse_address, sizeof(reuse_address)) < 0
            || bind(listener, address->ai_addr, address->ai_addrlen) < 0
            || listen(listener, SOCKET_LISTEN_BACKLOG_SIZE) < 0)
        {
            std::cerr << "Listening socket creation failure: " << std::strerror(errno) << '\n';
            close(listener);
            return -1;
        }
    }

    return listener;
}

Socket::Socket(char const* ip, char const* port)
{
    struct addrinfo hints = {};
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags    = AI_PASSIVE;

    struct addrinfo *address_list = NULL;

    int error = getaddrinfo(ip, port, &hints, &address_list);

    IRC_ASSERT_THROW(error != 0, std::string("Getaddrinfo failed: ") + gai_strerror(error));

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
        if (ipv4 && ipv6)
        {
            break;
        }
    }

    Socket listener;
    if (ipv6 != NULL)
    {
        std::cout << "Attempting to create IPv6 socket...\n";
        m_file_descriptor = create_listener_socket(ipv6);
    }
    if (ipv4 != NULL && !is_valid())
    {
        std::cout << "Attempting to create IPv4 socket...\n";
        m_file_descriptor = create_listener_socket(ipv4);
    }

    freeaddrinfo(address_list);

    IRC_ASSERT_THROW(!is_valid(), "No listening socket could be created.\n");

    std::cout << "Socket " << m_file_descriptor << " listening to " << port << ".\n";
}

ssize_t Socket::send(void const* source, size_t size) const
{
    ssize_t sent = ::send(m_file_descriptor, source, size, 0);

    IRC_ASSERT_THROW(sent == -1, std::string("Send error: ") + std::strerror(errno));

    return sent;
}

ssize_t Socket::receive(void* destination, size_t size) const
{
    ssize_t received = ::recv(m_file_descriptor, destination, size, 0);

    IRC_ASSERT_THROW(received == -1, std::string("Recv error: ") + std::strerror(errno));

    return received;
}

Socket Socket::accept() const
{
    //struct sockaddr_storage address;
    //socklen_t address_size = sizeof(address);

    std::cout << m_file_descriptor << " accepting inbound connection.\n";

    Socket client(::accept(m_file_descriptor, NULL, NULL));

    fcntl(client.get_file_descriptor(), F_SETFL, O_NONBLOCK);

    IRC_ASSERT_THROW(!client.is_valid(), std::string("Accepting incoming connection failed: ") + std::strerror(errno) + '\n');

    return client;
}
