#pragma once

//#include "Socket.hpp"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <exception>

class TCPServer {
private:
// Socket Server
	int	_server_socket_fd;
	struct sockaddr_in	_server_addr;
	int	_port;

public:
	TCPServer(); // Default Constructor
	TCPServer(TCPServer const& cpy); // Copy Constructor
	TCPServer operator= (TCPServer const& cpy); // Copy Assignment Operator
	~TCPServer(); // Destructor

	class SocketCreationFailed : public std::exception {
		virtual const char* what() const throw() {
            return ("Error: creating Server socket");
        }
	};

};
