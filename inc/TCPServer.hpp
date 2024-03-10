#pragma once

//#include "Socket.hpp"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <exception>
#include <unistd.h>

class TCPServer {
private:
// Socket Server
	int	_server_socket_fd;
	struct sockaddr_in	_server_addr;
	int	_port;
	int	_client_socket_fd;
	struct sockaddr_storage _client_addr;
	socklen_t _client_addr_size;

public:
	TCPServer(int port); // Default Constructor
	TCPServer(TCPServer const& cpy); // Copy Constructor
	TCPServer operator= (TCPServer const& cpy); // Copy Assignment Operator
	~TCPServer(); // Destructor

	void wait_for_connection();

	class SocketCreationFailed : public std::exception {
		virtual const char* what() const throw() {
            return ("Error: creating Server socket");
        }
	};

};
