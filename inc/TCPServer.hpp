#pragma once

//#include "Socket.hpp"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <exception>
#include <unistd.h>
#include <cerrno>

class TCPServer {
private:
// Sockets Server
	int	*_server_socket_fd;
	struct sockaddr_in	*_server_addr;
	int	*_ports;
	int	_nb_of_ports;

// for poll()
	struct pollfd _poll_fds[200];
	// timeout is set to 3 minutes
	int	_timeout;

	int	_client_socket_fd;
	int _client_count;
	struct sockaddr_storage _client_addr;
	socklen_t _client_addr_size;

public:
	TCPServer(int *ports, int nb_of_ports); // Default Constructor
	TCPServer(TCPServer const& cpy); // Copy Constructor
	TCPServer operator= (TCPServer const& cpy); // Copy Assignment Operator
	~TCPServer(); // Destructor

	void wait_for_connection();

	//using poll()
	void accept_connections();

	class SocketCreationFailed : public std::exception {
		virtual const char* what() const throw() {
            return ("Error: creating Server socket");
        }
	};

};
