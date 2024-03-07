#include "../inc/TCPServer.hpp"

TCPServer::TCPServer() : _port(8080) {
    std::cout << "TCPServer Default Constructor called" << std::endl;
    // AF_INET IPv4 vs IPv6
    // SOCK_STREAM FOR TCP vs UDP
    if ((_server_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw SocketCreationFailed();
    }

    // INADDR_ANY use my IPv4 address
    _server_addr.sin_family = AF_INET;
    _server_addr.sin_addr.s_addr = INADDR_ANY;
    // htons() converts values btw host and network byte order
    _server_addr.sin_port = htons(_port);

    // bind the socket to the specified IP and Port
    // Where did I specify the IP?
    // bind()
} // Default Constructor

TCPServer::TCPServer(TCPServer const& cpy) {
    std::cout << "TCPServer Copy Constructor called" << std::endl;
    (void)cpy;
    // To Do
} // Copy Constructor

TCPServer TCPServer::operator= (TCPServer const& cpy) {
    std::cout << "TCPServer Copy Assignment Operator called" << std::endl;
    (void)cpy;
    return (*this);
    // To Do
} // Copy Assignment Operator

TCPServer::~TCPServer() {
    std::cout << "TCPServer Destructor called" << std::endl;
} // Destructor