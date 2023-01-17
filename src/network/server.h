#ifndef GAME_SERVER_H
#define GAME_SERVER_H


#include <string>
#include <netinet/in.h>
#include "network_object.h"

class server : public network_object {
private:
    int serverSocketFd, clientSocketFd;
    sockaddr_in serverAddress, clientAddress;
public:
    server();

    void establishConnection() override;

    void send(std::string message) override;

    std::string receive() override;

    bool isServer() override;

    void close() override;
};


#endif //GAME_SERVER_H
