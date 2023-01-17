#include "game.h"
#include "network/client.h"
#include "network/server.h"

int main() {
    network_object *network = new server();
    return launch(network);
}
