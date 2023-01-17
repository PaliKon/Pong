#include <iostream>
#include "game.h"
#include "network/client.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./pong_client <server address>" << std::endl;
        return 0;
    }

    network_object *network = new client(argv[1]);
    return launch(network);
}
