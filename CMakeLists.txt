cmake_minimum_required(VERSION 3.18)
project(Game)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(libraries/glm)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(common src/game.cpp src/game.h src/collision/collision_object.cpp src/collision/collision_object.h src/collision/static_collision_box.cpp src/collision/static_collision_box.h src/collision/dynamic_collision_box.cpp src/collision/dynamic_collision_box.h src/network/server.cpp src/network/server.h src/network/client.cpp src/network/client.h src/network/network_object.cpp src/network/network_object.h src/game.h src/client_game.cpp src/server_game.cpp)
target_link_libraries(common PRIVATE glm)
target_link_libraries(common PRIVATE ncurses)

add_executable(pong-client src/client_game.cpp)
target_link_libraries(pong-client PRIVATE common)
target_link_libraries(pong-client PRIVATE glm)
target_link_libraries(pong-client PRIVATE ncurses)
target_link_libraries(pong-client PRIVATE Threads::Threads)

add_executable(pong-server src/server_game.cpp)
target_link_libraries(pong-server PRIVATE common)
target_link_libraries(pong-server PRIVATE glm)
target_link_libraries(pong-server PRIVATE ncurses)
target_link_libraries(pong-server PRIVATE Threads::Threads)