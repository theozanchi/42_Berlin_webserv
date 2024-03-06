#pragma once

#include "webserv.hpp"
#include <sys/socket.h>

class Socket {

public:
	Socket(); // Default Constructor
	Socket(Socket const& cpy); // Copy Constructor
	Socket operator=(Socket const& cpy); // Copy Assignment operator
	~Socket(); // Destructor

	// Setter Functions for private members

};
