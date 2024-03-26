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
#include <fcntl.h>
#include <csignal>
#include <cstdlib>
#include <netdb.h>
#include <sstream>

#include "Request.hpp"
#include "Response.hpp"
#include "Configuration.hpp"
#include "webserv.hpp"

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

extern bool sigint_flag;

class TCPServer {
private:
	Configuration _config;
// Sockets Server
	int	*_server_socket_fd;
	struct sockaddr_in	*_server_addr;
	int	*_ports;
	int _nb_of_servers;
	int	_nb_of_ports;

// for poll()
	struct pollfd 	_poll_fds[200];
	nfds_t 			_n_poll_fds;
	// timeout is set to 3 minutes
	int	_timeout;

	int	_client_socket_fd;
	struct sockaddr_storage _client_addr;
	socklen_t _client_addr_size;

	int is_server_socket(int pollfd);

	TCPServer(); // Default Constructor

public:
	TCPServer(int *ports, int nb_of_ports, std::string *hosts); // Parametric Constructor int array
	TCPServer(Configuration& config); // Parametric Constructor Config file
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
