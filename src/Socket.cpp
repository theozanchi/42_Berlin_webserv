#include "../inc/Socket.hpp"

Socket::Socket() {
	std::cout << "Socket Default Constructor called" << std::endl;
}// Default Constructor

Socket::Socket(Socket const& cpy) {
	std::cout << "Socket Copy Constructor called" << std::endl;
} // Copy Constructor

Socket Socket::operator=(Socket const& cpy) {
	std::cout << "Socket Copy Assignment operator called" << std::endl;
} // Copy Assignment operator

Socket::~Socket() {
	std::cout << "Socket Destructor called" << std::endl;
} // Destructor
