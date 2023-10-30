#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>

#define PROTOCOL_TCP 6 // At least on MacOS?
#define IRC_PORT 6667

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	//Create a socket for our server, can't be used without a name/address
	int server_socket = socket(PF_INET, SOCK_STREAM,  PROTOCOL_TCP);
	if (server_socket == -1) 
	{
		std::perror("Failed to open socket");
		exit(1);
	}

	// Descriptor for IPv4 socket address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;        // IPv4 
	server_address.sin_port = htons(IRC_PORT);  // Converts host byte order int to network byte order short
	server_address.sin_addr.s_addr = INADDR_ANY;// 0.0.0.0

	//Binds an address to the socket
	if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1)
	{
		std::perror("Failed to bind socket");
		exit(1);
	}

	// Listen for inbound connections from the server socket
	if (listen(server_socket, 1) == -1)
	{
		std::perror("Failed to listen to inbound connections from server socket");
		exit(1);
	}

	// Accept inbound connection
	int client_socket = accept(server_socket, NULL, NULL);


	// Send messae to client
	std::string message("Hello world");

	int flags = 0;
	if (send(client_socket, message.data(), message.size(), flags) != static_cast<ssize_t>(message.size()))
	{
		std::perror("Failed to send message");
		exit(1);
	}

	// Close sockets
	close(server_socket);
	close(client_socket);

	return 0;
}
