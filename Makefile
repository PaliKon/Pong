all: server client

COMMON_SOURCES = src/game.cpp src/game.h src/collision/collision_object.cpp src/collision/collision_object.h src/collision/static_collision_box.cpp src/collision/static_collision_box.h src/collision/dynamic_collision_box.cpp src/collision/dynamic_collision_box.h src/network/server.cpp src/network/server.h src/network/client.cpp src/network/client.h src/network/network_object.cpp src/network/network_object.h src/game.h src/client_game.cpp src/server_game.cpp
SERVER_SOURCES = src/server_game.cpp $(COMMON_SOURCES)
CLIENT_SOURCES = src/client_game.cpp $(COMMON_SOURCES)

CFLAGS += -Ilibraries/glm

server: $(SERVER_SOURCES)
	g++ -o $(CFLAGS) server $(SERVER_SOURCES)

client: $(CLIENT_SOURCES)
	g++ -o $(CFLAGS) client $(CLIENT_SOURCES)

clean:
	rm -f server client
