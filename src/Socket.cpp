#include "Socket.hpp"

#include "Debug.hpp"

#include <string>
#include <netdb.h>

static int create_listener_socket(struct addrinfo const* address)
{
    int listener = socket(address->ai_family, address->ai_socktype, address->ai_protocol);

    if (listener >= 0)
    {
        // Remove "address already in use" error message
        int reuse_address = true;
        if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &reuse_address, sizeof(reuse_address)) < 0
            || bind(listener, address->ai_addr, address->ai_addrlen) < 0
            || listen(listener, 10) < 0)
        {
            close(listener);
            return -1;
        }
    }

    return listener;
}

Socket Socket::listen(char const* address, char const* port)
{
    struct addrinfo hints = {};
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags    = AI_PASSIVE;

    struct addrinfo *address_list = NULL;

    int error = getaddrinfo(address, port, &hints, &address_list);

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

    Socket listener;
    if (ipv6 != NULL)
    {
        listener.file_descriptor = create_listener_socket(ipv6);

        if (listener.file_descriptor < 0)
        {
            std::cerr << "IPv6 listening socket creation failure: " << std::strerror(errno) << '\n';
        }
    }
    if (ipv4 != NULL && listener.file_descriptor < 0)
    {
        listener = create_listener_socket(ipv4);

        if (listener.file_descriptor < 0)
        {
            std::cerr << "IPv4 listening socket creation failure: " << std::strerror(errno) << '\n';
        }
    }

    freeaddrinfo(address_list);

    IRC_ASSERT_THROW(listener.file_descriptor < 0, "No listening socket could be created.\n");

    return listener;
}

Socket Socket::accept(struct sockaddr_storage* address)
{
    static socklen_t address_size = sizeof(*address);
    Socket inbound(::accept(file_descriptor, (struct sockaddr*)(address), &address_size));

    IRC_ASSERT_THROW(inbound.file_descriptor < 0, std::string("Accepting incoming connection failed") + std::strerror(errno));

    return inbound;
}
