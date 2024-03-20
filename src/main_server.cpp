#include "../inc/TCPServer.hpp"

// TO DO
// different host:port is important for handling http request
// our sockets will only listen on localhost:port to only accessible on local machine
// check for memleaks

bool sigint_flag = false;

void    handle_sigint(int sig)
{
    (void)sig;
    std::cout << std::endl << "Sigint received" << std::endl;
    sigint_flag = true;
    return ;
}

int main() {
    int port[3] = { 8080, 9002, 8090 };
    int nb_of_ports = 3;

    try {
        TCPServer aServer(port, nb_of_ports);

        signal(SIGINT, &handle_sigint);
        //aServer.wait_for_connection();
        aServer.accept_connections();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
