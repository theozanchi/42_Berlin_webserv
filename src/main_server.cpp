#include "../inc/TCPServer.hpp"

// TO DO make Server listen to multiple ports!
// IDEA for each port declare a TCPServer instance in a separate process not allowed (fork())
// Not allowed for each server declare a 


int main() {
    TCPServer aServer(8080);

    aServer.wait_for_connection();

    return 0;
}