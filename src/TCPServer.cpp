#include "../inc/TCPServer.hpp"

// To Do
// For Each port I will create a Server Socket that is bind and listens to the port
// all will call the wait for connection function that will keep track of the client fds?
// implement the Crtl + C Signal to end program with mem leaks

TCPServer::TCPServer(int *ports, int nb_of_ports) : _nb_of_ports(nb_of_ports), _timeout(3 * 60 * 1000), _client_socket_fd(-1), _client_count(0) {
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
        // SOCK_NONBLOCK to set socket in non-blocking mode SOCK_STREAM | SOCK_NONBLOCK
        if ((_server_socket_fd[i] = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
            throw SocketCreationFailed();
        }

        // for my mac only
        fcntl(_server_socket_fd[i], F_SETFL, O_NONBLOCK);

        // to avoid bind() error "port already in use" when rerunning the server
        if (setsockopt(_server_socket_fd[i], SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1)
            throw SocketCreationFailed();

        // bind the socket to the specified IP and Port
        // Where did I specify the IP?
        if (bind(_server_socket_fd[i], (struct sockaddr *)&_server_addr[i], sizeof _server_addr[i]) < 0)
            throw SocketCreationFailed();

        // wait for incoming connections
        // they are being queued and limited to system max connections
        if (listen(_server_socket_fd[i], SOMAXCONN) < 0)
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

int TCPServer::is_server_socket(int pollfd) {
    for (int j = 0; j < _nb_of_ports; j++)
    {
        if (pollfd == _server_socket_fd[j])
        {
            std::cout << "It's the server socket" << std::endl;
            return (j);
        }
    }
    std::cout << "It's a client socket" << std::endl;
    return (-1);
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
    // The IBM version is a blocking I/O operation
    const char* msg = "HTTP/1.1 200 OK\r\nContent-Type: text/html\n\n<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n<title>A simple webpage</title>\n</head>\n<body>\n \
                        <h1>Simple HTML webpage</h1>\n<p>Hello, world!</p>\n</body>\n</html>\n";
    char  recv_msg[1024];
    (void)msg;
    (void)_timeout;

    //https://www.linuxtoday.com/blog/multiplexed-i0-with-poll/
    int     rt_val = 1;

    // initialize the pollfd structure
    std::memset(_poll_fds, '\0', sizeof _poll_fds);

    // set up the initial listening sockets
    // maybe I have to call the accept_connection on each server socket?
    // POLLIN | POLLOUT will monitor single fd for reading and writing
    for (int i = 0; i < _nb_of_ports; i++)
    {
        _poll_fds[i].fd = _server_socket_fd[i];
        _poll_fds[i].events = POLLIN; // listening sockets
        _poll_fds[i].revents = 0;
        // on return from poll()
        //_poll_fds[i].revents will be filled with same POLLIN POLLOUT values
        // indicating which of the interesting events the fd is ready for
        // OR POLLERR POLLHUP POLLNVAL on error
    }

    // n_poll_fds will keep track of the nb of fds in struct pollfd
    nfds_t n_poll_fds;
    int numfds = _nb_of_ports;
     // not sure about this line
    // we would always reset the number

    // my server is currently blocking other incoming connections
    while (true)
    {
        n_poll_fds = numfds;
        // monitor the listening fds for readiness for reading
        rt_val = poll(_poll_fds, n_poll_fds, _timeout);
        if (rt_val < 0)
        {
            std::cout << "poll() failed" << std::endl;
            break ;
        }
        // check if the time limit is reached when timeout is set
        else if (rt_val == 0)
        {
            std::cout << "poll() timed out" << std::endl;
            break ;
        }
        else
        {
            // one or more fds are readable. Need to determine which ones
            // loop through to find fd that returned POLLIN
            // determine whether it's the listening or the active connection
            for (unsigned int i = 0; i < n_poll_fds; i++)
            { 
                if (_poll_fds[i].fd <= 0)
                    continue;
            
                // fd is ready for reading
                if (_poll_fds[i].revents & POLLIN)
                {
                    // request for new connection to server
                    int j = is_server_socket(_poll_fds[i].fd);
                    if (j >= 0)
                    {
                        _client_addr_size = sizeof _client_addr;
                        _client_socket_fd = accept(_server_socket_fd[j], (struct sockaddr *)&_client_addr, &_client_addr_size);
                        if (_client_socket_fd == -1)
                        {
                            std::cout << " accept() failed" << std::endl;
                            break ;
                        }
                        fcntl(_client_socket_fd, F_SETFL, O_NONBLOCK);
                        // ad new fd to pollfds
                        std::cout << " accept() client " << _client_socket_fd << std::endl;
                        _poll_fds[numfds].fd = _client_socket_fd;
                        _poll_fds[numfds].events = POLLIN;
                        numfds++;
                        _client_count++;
                    }
                    // data from an existing connection, receive it
                    else
                    {
                        std::memset(&recv_msg, '\0', sizeof recv_msg);
                        ssize_t numbytes = recv(_poll_fds[i].fd, &recv_msg, sizeof recv_msg, 0);

                        if (numbytes < 0)
                            std::cout << "recv() failed" << std::endl;
                        else if (numbytes == 0)
                        {
                            // 0 means connection closed by client
                            std::cout << "Socket " << _poll_fds[i].fd << "closed by client" << std::endl;
                            if (close(_poll_fds[i].fd) == -1)
                                std::cout << " close() error" << std::endl;
                            // make it negative so that it is ignored in the future
                            _poll_fds[i].fd *= -1;
                            _poll_fds[i].revents = 0;
                        }
                        else
                        {
                            // process data from client
                            std::cout << "Here parsing of request should happen" << std::endl;
                            std::cout << "And appropriate HTTP Response should be send" << std::endl;
                            send(_client_socket_fd, msg, std::strlen(msg), 0);
                        }
                    }
                }
            } 
        }
    }
}

/*
            // old code 
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
            if (_poll_fds[i].fd == _server_socket_fd[0])
            {
                std::cout << "Server Socket " << _server_socket_fd[0] << " is readable" << std::endl;

                // accept all incoming connections
                // they are queued up on the listening socket
                // before we loop back and call poll again
                do
                {
                    _client_socket_fd = accept(_server_socket_fd[0], NULL, NULL);
                    //what about getsockname()?
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
            else
            {
                // it is not the listening socket
                // therefor an existing connection must be readable
                std::cout << "Client Socket " << _poll_fds[i].fd << " is readable" << std::endl;
                close_conn = false;

                // receive all incoming data on this socket
                // before we loop back and call poll again
                while(true)
                {
                    rt_val = recv(_poll_fds[i].fd, buffer, sizeof buffer, 0);
                    if (rt_val < 0)
                    {
                        if (errno != EWOULDBLOCK)
                        {
                            std::cout << " recv() failed" << std::endl;
                            close_conn = true;
                        }
                        break ;
                    }

                    // check if client has been closed by client
                    if (rt_val == 0)
                    {
                        std::cout << " Connection closed" << std::endl;
                        close_conn = true;
                        break ;
                    }

                    // Data was received
                    len = rt_val;
                    std::cout << len << " bytes received" << std::endl;
                    rt_val = send(_poll_fds[i].fd, msg, std::strlen(msg), 0);
                    if (rt_val < 0)
                    {
                        std::cout << " send() failed" << std::endl;
                        close_conn = true;
                        break ;
                    }
                }

                // if close_conn true
                // need to clean up active connection
                // removing fd

            }


        }


    }
}*/
