#include <sys/socket.h>
#include <arpa/inet.h>
#include "client.h"
#include <unistd.h>

client::client(std::string address) {
    clientSocketFd = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);

    inet_pton(AF_INET, address.c_str(), &serverAddress.sin_addr);
}

void client::establishConnection() {
    serverSocketFd = connect(clientSocketFd, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
}

void client::send(std::string message) {
    ::send(clientSocketFd, message.c_str(), message.length(), 0);
}

std::string client::receive() {
    ssize_t bytes = recv(clientSocketFd, buffer, 1024, 0);
    if (bytes > 0) {
        return {buffer};
    }

    return {""};
}

bool client::isServer() {
    return false;
}

void client::close() {
    ::close(serverSocketFd);
}
