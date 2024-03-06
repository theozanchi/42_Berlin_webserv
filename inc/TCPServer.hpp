#pragma once

#include "Socket.hpp"

class TCPServer {
private:
	Socket	server;

public:
	TCPServer(); // Default Constructor
	TCPServer(TCPServer const& cpy); // Copy Constructor
	TCPServer operator= (TCPServer const& cpy); // Copy Assignment Operator
	~TCPServer(); // Destructor

};
