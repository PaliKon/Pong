#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "server.h"

server::server() {
    // Create socket
    serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);

    // Create serverAddress
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to serverAddress
    bind(serverSocketFd, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    listen(serverSocketFd, 1);
}

void server::establishConnection() {
    // Accept connection
    int len = sizeof(clientAddress);
    clientSocketFd = accept(serverSocketFd, (struct sockaddr *) &clientAddress, (socklen_t *) &len);
}

void server::send(std::string message) {
    ::send(clientSocketFd, message.c_str(), message.length(), 0);
}

std::string server::receive() {
    ssize_t bytes = recv(clientSocketFd, buffer, 1024, 0);
    if (bytes > 0) {
        return {buffer};
    }

    return {""};
}

bool server::isServer() {
    return true;
}

void server::close() {
    ::close(clientSocketFd);
    shutdown(serverSocketFd, SHUT_RDWR);
}
