#include "../inc/TCPServer.hpp"

// TO DO make Server listen to multiple ports!
// IDEA for each port declare a TCPServer instance in a separate process not allowed (fork())
// Not allowed for each server declare a
// Server doesn"t listen to another port than 8080


int main() {
    TCPServer aServer(8080);
    TCPServer bServer(9002);

    aServer.wait_for_connection();
    bServer.wait_for_connection();

    return 0;
}
