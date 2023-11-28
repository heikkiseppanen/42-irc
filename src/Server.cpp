#include "Server.hpp"
#include "Debug.hpp"

#include <iostream>

Server::Server() : m_eventloop() {}

Server::~Server() {}

void Server::run()
{
    while (1)
    {
        m_eventloop.handle();
    }
}

//    {
//            if (client->revents & POLLIN)
//            {
//                // Should be stored for each socket to handle messages not coming in whole
//                char socket_stream[512] = {};
//
//                int read_bytes = recv(client->fd, socket_stream, sizeof(socket_stream), 0);
//
//                if (read_bytes < 0)
//                {
//                    perror("recv:");
//                }
//                else if (read_bytes == 0)
//                {
//                    close(client->fd);
//                    std::swap(*client, m_socket_list.back());
//                    m_socket_list.pop_back();
//                }
//                else
//                {
//                    for(std::vector<Socket>::iterator destination = m_socket_list.begin() + 1; destination != m_socket_list.end(); ++destination)
//                    {
//                        if (destination->fd == client->fd || (destination->revents & POLLOUT) == 0)
//                        {
//                            continue;
//                        }
//                        if (send(destination->fd, socket_stream, read_bytes, 0) == -1)
//                        {
//                            perror("send:");
//                        }
//                    }
//                }
//            }
//        }
//        
//        Socket& listener = m_socket_list.front();
//
//        if (listener.revents & POLLIN)
//        {
//            struct sockaddr_storage address;
//            socklen_t address_size = sizeof(address);
//            
//            Socket client = {};
//            client.fd = accept(listener.fd, (struct sockaddr *)&address, &address_size);
//            client.events = POLLIN | POLLOUT;
//
//            if (client.fd == -1)
//            {
//                std::perror("accept");
//            }
//            else
//            {
//                m_socket_list.push_back(client);
//
//                char buf[INET6_ADDRSTRLEN];
//
//                void *ip;
//
//                if (address.ss_family == AF_INET)
//                {
//                    ip = &(((struct sockaddr_in *)(&address))->sin_addr);
//                }
//                else
//                {
//                    ip = &(((struct sockaddr_in6 *)(&address))->sin6_addr);
//                }
//
//                printf("pollserver: new connection from %s on socket %d\n",
//                    inet_ntop(address.ss_family, ip, buf, INET6_ADDRSTRLEN), client.fd);
//            }
//        }
//    }
//}
