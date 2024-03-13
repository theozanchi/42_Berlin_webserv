#include "../inc/TCPServer.hpp"

// To Do
// For Each port I will create a Server Socket that is bind and listens to the port
// all will call the wait for connection function that will keep track of the client fds?
// implement the Crtl + C Signal to end program with mem leaks

TCPServer::TCPServer(int *ports, int nb_of_ports) : _nb_of_ports(nb_of_ports), _timeout(30 * 1000), _client_socket_fd(-1), _client_count(0) {
    std::cout << "TCPServer Default Constructor called" << std::endl;
    // I could also call getaddrinfo() to fill struct addrinfo
    // not sure if it fill in struct sockaddr as well
    // then use the struct addrinfo to pass parameters to the functions bind(), listen() etc
    // You use getaddrinfo() to do nameserver DNS lookup on hostname like "www.example.com"
    // https://beej.us/guide/bgnet/html/#port-numbers
    // sin_family Address Family
    // each port needs its own socket and therefore data structure and fd
    _server_addr = new struct sockaddr_in[nb_of_ports];
    _server_socket_fd = new int[nb_of_ports];
    _ports = new int[nb_of_ports];
    int yes = 1;

    for (int i = 0; i < nb_of_ports; i++)
    {
        _ports[i] = ports[i];
        _server_addr[i].sin_family = AF_INET;
        // sin_addr Internet Address in Network Byte Order
        // INADDR_ANY use my IPv4 address
        _server_addr[i].sin_addr.s_addr = INADDR_ANY;
        // sin_port Port Number in Network Byte Order
        // htons() converts values btw host and network byte order
        _server_addr[i].sin_port = htons(_ports[i]);
        std::memset(_server_addr[i].sin_zero, '\0', sizeof _server_addr[i].sin_zero);

        // AF_INET IPv4 vs IPv6
        // SOCK_STREAM FOR TCP vs UDP
        // 0 chooses proper protocol for given type or getprotobyname to look protocol you want
        if ((_server_socket_fd[i] = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
            throw SocketCreationFailed();
        }

        // to avoid bind() error "port already in use" when rerunning the server
        if (setsockopt(_server_socket_fd[i], SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1)
            throw SocketCreationFailed();

        // use ioctl() API to set socket to be nonblocking
        // all sockets for the incoming inherit the nonblocking state from the listening socket
        // see IBM for that, subject doesnt allow this function!
        //if (ioctl(_server_socket_fd[i], FIONBIO, &yes) < 0)
          //  throw SocketCreationFailed();

        // bind the socket to the specified IP and Port
        // Where did I specify the IP?
        if (bind(_server_socket_fd[i], (struct sockaddr *)&_server_addr[i], sizeof _server_addr[i]) < 0)
            throw SocketCreationFailed();

        // wait for incoming connections
        // they are being queued and limited to 20 connections
        if (listen(_server_socket_fd[i], 20) < 0)
            throw SocketCreationFailed();

    }
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

// We need to handle Ctrl+C Signal to exit pgm in clean way
TCPServer::~TCPServer() {
    std::cout << "TCPServer Destructor called" << std::endl;
    delete [] _server_socket_fd;
    delete [] _server_addr;
    delete [] _ports;
    //close(_client_socket_fd);
   // close(_server_socket_fd);
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
        for (int i = 0; i < _nb_of_ports; i++)
        {
            _client_socket_fd = accept(_server_socket_fd[i], (struct sockaddr *)&_client_addr, &_client_addr_size);
            send(_client_socket_fd, msg, std::strlen(msg), 0); // send http response for testing
        }
    }
}

void TCPServer::accept_connections() {
    // To Do
    // ibm.com/docs/en/i/7.4?topic=designs-using-poll-instead-select
    // IBM using poll() instead of select()
    // poll() API allows the process to wait for an event to occur
    // then wakes up the process
    // return values of poll()
    // 0 indicates process time out.
    // -1 indicates process has failed
    // 1 indicates only one fd is ready to be processed and is processed only if it is server(listening) socket
    // 1++ multiple fds are waiting to be processed. poll() API allows simultaneous connection with all fd in the queue on the listening socket
    // accept() and recv() APIs are completed when the EWOULDBLOCK is returned

    // flag to stop server
    bool    end_server = false;
    int     poll_rt_val = 1;

    // initialize the pollfd structure
    std::memset(_poll_fds, '\0', sizeof _poll_fds);

    // set up the initial listening sockets
    for (int i = 0; i < _nb_of_ports; i++)
    {
        _poll_fds[i].fd = _server_socket_fd[i];
        _poll_fds[i].events = POLLIN;

    }

    while (end_server == false)
    {
        poll_rt_val = poll(_poll_fds, _nb_of_ports, _timeout);
        if (poll_rt_val < 0)
        {
            std::cout << "poll() failed" << std::endl;
            break ;
        }
        // check if the time limit is reached
        if (poll_rt_val == 0)
        {
            std::cout << "poll() timed out" << std::endl;
            break;
        }

        // one or more fds are readable. Need to determine which ones
        // loop through to find fd that returned POLLIN
        // determine whether it's the listening or the active connection
        for (int i = 0; i < _nb_of_ports; i++)
        {
            if (_poll_fds[i].revents == 0)
                continue ;

            if (_poll_fds[i].revents != POLLIN)
            {
                std::cout << "poll() error revents " << _poll_fds[i].revents << std::endl;
                end_server = true;
                break ;
            }

            // not sure if the arrays actually stay synched
            // maybe I have to compare it to each possible _server_socket_fd
            if (_poll_fds[i].fd == _server_socket_fd[i])
            {
                std::cout << "Server Socket " << _server_socket_fd[i] << " is readable" << std::endl;

                // accept all incoming connections
                // they are queued up on the listening socket
                // before we loop back and call poll again
                do
                {
                    _client_socket_fd = accept(_server_socket_fd[i], NULL, NULL);
                    if (_client_socket_fd < 0)
                    {
                        // errno = EWOULDBLOCK is good it means
                        // _server_socket_fd[i] is in nonblocking mode and
                        // no connections are in the queue
                        if (errno != EWOULDBLOCK)
                        {
                            std::cout << "accept() failed" << std::endl;
                            end_server = true;
                        }
                        break ;
                    }

                    // add new incoming connection to the pollfd structure
                    std::cout << "new incoming connection " << _client_socket_fd << std::endl;
                    _poll_fds[_nb_of_ports + _client_count].fd = _client_socket_fd;
                    _poll_fds[_nb_of_ports + _client_count].events = POLLIN;
                    _client_count++;

                    // loop back up and accept another incoming connection
                } while (_client_socket_fd != -1);
            }
        }


    }
}
