#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <poll.h>
#include <cstdlib>

#include <arpa/inet.h>

#define PORT "6667" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void add_fuzz(std::vector<std::string> fuzz)
{
    std::vector<std::string> starts = {"PRIVMSG",
    "JOIN",
    "QUIT",
    "KICK",
    "INVITE",
    "TOPIC",
    "MODE",
    "PART",
    "NICK",
    "USER",
    "PASS",
    "PING",
    "PONG",
    "CAP"};

    static bool rand_seeded = false;
    static std::string letter_set;

    if (!rand_seeded)
    {
        std::srand(std::time(nullptr));
        rand_seeded = true;
        char a = ' ';
        while(a < 126)
        {
            letter_set += a;
            a++;
        }
    }
    constexpr int e = 126 - 32;

    std::string fuzz_str;

    for (int i = 0; i < 5; i++)
    {
        fuzz_str = starts[std::rand() % 14];
        for (int j = 0; j < 120; j++)
        {
            fuzz_str += letter_set[std::rand() % 94];
        }
        fuzz.push_back(fuzz_str + "\r\n");
    }
}

int main(int argc, char *argv[])
{
    int sockfd, numbytes;  
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 2)
    {
        std::cout << "Usage: ./fuzzer <fuzz_count>\n";
        return -1;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo("localhost", PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    // inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
    //         s, sizeof s);
    // printf("client: connecting to %s\n", s);
    std::cout << "Connected\n";

    freeaddrinfo(servinfo); // all done with this structure

    struct pollfd pfds[1];
    pfds[0].fd = sockfd;
    pfds[0].events = POLLIN | POLLOUT;

    char buf[1024 + 1];
    std::vector<std::string> fuzz_strings;
    fuzz_strings.push_back("NICK a\r\n");
    fuzz_strings.push_back("USER a a a a\r\n");

    unsigned int total = std::stoul(argv[1]);

    for (unsigned int fuzz_count = 0; fuzz_count < total; fuzz_count++)
    {
        if (fuzz_strings.empty())
        {
            add_fuzz(fuzz_strings);
        }

        int poll_count = poll(pfds, 1, 1000);
        assert(poll_count != -1);

        if (poll_count < 1)
            continue;
        
        if (pfds[0].revents & POLLIN)
        {
            buf[recv(pfds[0].fd, buf, 1024, 0)] = '\0';
            std::cout << "recv: " << buf << "\n";
        }
        else if (pfds[0].revents & POLLOUT)
        {
            std::string msg = fuzz_strings.back();
            fuzz_strings.pop_back();
            send(pfds[0].fd, msg.c_str(), msg.length(), 0);
            std::cout << "sent: " << msg << "\n";
        }
    }
    close(sockfd);

    return 0;
}
