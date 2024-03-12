#include "../inc/TCPServer.hpp"

// To Do
// For Each port I will create a Server Socket that is bind and listens to the port
// all will call the wait for connection function that will keep track of the client fds?
// implement the Crtl + C Signal to end program with mem leaks

TCPServer::TCPServer(int port) : _port(port) {
    std::cout << "TCPServer Default Constructor called" << std::endl;
    // I could also call getaddrinfo() to fill struct addrinfo
    // not sure if it fill in struct sockaddr as well
    // then use the struct addrinfo to pass parameters to the functions bind(), listen() etc
    // You use getaddrinfo() to do nameserver DNS lookup on hostname like "www.example.com"
    // https://beej.us/guide/bgnet/html/#port-numbers
    // sin_family Address Family
    _server_addr.sin_family = AF_INET;
    // sin_addr Internet Address in Network Byte Order
    // INADDR_ANY use my IPv4 address
    _server_addr.sin_addr.s_addr = INADDR_ANY;
    // sin_port Port Number in Network Byte Order
    // htons() converts values btw host and network byte order
    _server_addr.sin_port = htons(_port);
    std::memset(_server_addr.sin_zero, '\0', sizeof _server_addr.sin_zero);

    // AF_INET IPv4 vs IPv6
    // SOCK_STREAM FOR TCP vs UDP
    // 0 chooses proper protocol for given type or getprotobyname to look protocol you want
    if ((_server_socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        throw SocketCreationFailed();
    }

    int yes = 1;
    // to avoid bind() error "port already in use" when rerunning the server
    if (setsockopt(_server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1)
        throw SocketCreationFailed();

    // bind the socket to the specified IP and Port
    // Where did I specify the IP?
    if (bind(_server_socket_fd, (struct sockaddr *)&_server_addr, sizeof _server_addr) < 0)
        throw SocketCreationFailed();

    // wait for incoming connections
    // they are being queued and limited to 20 connections
    if (listen(_server_socket_fd, 20) < 0)
        throw SocketCreationFailed();


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
    close(_client_socket_fd);
    close(_server_socket_fd);
    //freeaddrinfo(return value of getaddrinfo)
} // Destructor

void TCPServer::wait_for_connection() {
    // To Do
    // non-blocking read from socket with timeout
    const char* msg = "HTTP/1.1 200 OK\r\nContent-Type: text/html\n\n<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n<title>A simple webpage</title>\n</head>\n<body>\n \
                        <h1>Simple HTML webpage</h1>\n<p>Hello, world!</p>\n</body>\n</html>\n";

    _client_addr_size = sizeof _client_addr;
    while (true)
    {
        _client_socket_fd = accept(_server_socket_fd, (struct sockaddr *)&_client_addr, &_client_addr_size);
        send(_client_socket_fd, msg, std::strlen(msg), 0); // send http response for testing
    }
}
