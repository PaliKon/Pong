#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H


#include <string>
#include <netinet/in.h>
#include "network_object.h"

class client : public network_object {
private:
    int serverSocketFd, clientSocketFd;
    sockaddr_in serverAddress, clientAddress;
public:
    client(std::string address);

    void establishConnection() override;

    void send(std::string message) override;

    std::string receive() override;

    bool isServer() override;

    void close() override;
};


#endif //GAME_CLIENT_H
