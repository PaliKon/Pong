#ifndef GAME_NETWORK_OBJECT_H
#define GAME_NETWORK_OBJECT_H


#include <string>

class network_object {
protected:
    char buffer[1024] = {0};
public:
    virtual void establishConnection() = 0;

    virtual void send(std::string message) = 0;

    virtual std::string receive() = 0;

    virtual bool isServer() = 0;

    virtual void close() = 0;
};


#endif //GAME_NETWORK_OBJECT_H
