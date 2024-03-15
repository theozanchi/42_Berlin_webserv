#include "../inc/TCPServer.hpp"

// TO DO make Server listen to multiple ports!
// IDEA for each port declare a TCPServer instance in a separate process not allowed (fork())
// Not allowed for each server declare a
// Server doesn"t listen to another port than 8080 on school maschine
// Server tested successfully to serve on three ports on my machine


int main() {
    int port[1] = { 8080 };
    int nb_of_ports = 1;

    TCPServer aServer(port, nb_of_ports);

    aServer.wait_for_connection();
    //aServer.accept_connections();

    return 0;
}
