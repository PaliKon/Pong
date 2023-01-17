#include <ncurses.h>
#include <unistd.h>
#include <thread>
#include "game.h"
#include "collision/collision_object.h"
#include "collision/dynamic_collision_box.h"
#include "collision/static_collision_box.h"

network_object *network;

const int ticksPerSecond = 10;
const int winHeight = 30;
const int winWidth = 60;
const int paddleSize = 13;

int currentTick = 0;
bool gameInProgress = true;
bool isWinner = false;

std::vector<std::unique_ptr<collision_object>> collision_objects;

glm::ivec2 ballVelocity = glm::ivec2(winWidth / 2, winHeight / 2);
glm::ivec2 playerPos = glm::ivec2(winWidth / 2, winHeight - 3);
glm::ivec2 opponentPos = glm::ivec2(winWidth / 2, 2);

glm::ivec2 ballDirection;

std::thread networkThread;

int launch(network_object *net) {
    network = net;
    initScreen();
    renderConnectionScreen();
    network->establishConnection();

    init();

    while (gameInProgress) {
        update();
        usleep(1000000 / ticksPerSecond);
        ++currentTick;
    }

    renderGameOver();
    network->close();
    networkThread.join();
    return 0;
}

void initScreen() {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);
    resize_term(30, 60);
    keypad(stdscr, true);
    curs_set(0);
}

void init() {
    initCollisionObjects();
    networkThread = std::thread(networkReceive);
    ballDirection = network->isServer() ? glm::ivec2(1, 1) : glm::ivec2(-1, -1);
}

void initCollisionObjects() {
    // Player paddle collision box
    collision_objects.push_back(
            std::make_unique<dynamic_collision_box>(
                    []() { return glm::ivec2(playerPos.x - paddleSize / 2, playerPos.y); },
                    []() { return glm::ivec2(playerPos.x + paddleSize / 2, playerPos.y); },
                    false, true
            )
    );

    // Opponent paddle collision box
    collision_objects.push_back(
            std::make_unique<dynamic_collision_box>(
                    []() { return glm::ivec2(opponentPos.x - paddleSize / 2, opponentPos.y); },
                    []() { return glm::ivec2(opponentPos.x + paddleSize / 2, opponentPos.y); },
                    false, true
            )
    );

    // Side walls
    collision_objects.push_back(
            std::make_unique<static_collision_box>(
                    glm::ivec2(0, 0), glm::ivec2(0, winHeight),
                    true, false
            )
    );
    collision_objects.push_back(
            std::make_unique<static_collision_box>(
                    glm::ivec2(winWidth - 1, 0), glm::ivec2(winWidth - 1, winHeight),
                    true, false
            )
    );
}

void update() {
    clear();
    render();
    refresh();

    if (currentTick % 3 == 0) {
        network->send(std::to_string(playerPos.x));
    }

    handleInputs();
    updateBall();
    checkResult();
}

void updateBall() {
    if (currentTick % 3 != 0) return;

    ballVelocity += ballDirection;
    for (auto &collision_object: collision_objects) {
        if (collision_object->willCollide(ballVelocity, ballDirection)) {
            ballDirection = collision_object->bounce(ballDirection);
            break;
        }
    }
}

void checkResult() {
    if (ballVelocity.y > winHeight - 2) {
        gameInProgress = false;
        isWinner = false;
    } else if (ballVelocity.y < 1) {
        gameInProgress = false;
        isWinner = true;
    }
}

void render() {
    box(stdscr, 0, 0);

    renderBall();
    renderPaddle(playerPos);
    renderPaddle(opponentPos);
}

void renderBall() {
    mvaddch(ballVelocity.y, ballVelocity.x, 'o');
}

void renderPaddle(glm::ivec2 &pos) {
    for (int x = pos.x - (paddleSize / 2); x <= pos.x + (paddleSize / 2); ++x) {
        mvaddch(pos.y, x, '=');
    }
}

void renderGameOver() {
    clear();
    mvprintw(winHeight / 2 - 2, winWidth / 2 - 5, "Game Over!");
    if (isWinner) {
        mvprintw(winHeight / 2 - 1, winWidth / 2 - 3, "Winner");
    } else {
        mvprintw(winHeight / 2 - 1, winWidth / 2 - 3, "Loser");
    }
    mvprintw(winHeight / 2 + 1, winWidth / 2 - 11, "(Press any key to exit)");
    refresh();

    nodelay(stdscr, false);
    getch();
    endwin();
}

void renderConnectionScreen() {
    clear();
    if (network->isServer()) {
        mvprintw(winHeight / 2 - 1, winWidth / 2 - 20, "Server started - Listening on port 8080");
        mvprintw(winHeight / 2 + 1, winWidth / 2 - 12, "(Waiting for connection)");
    } else {
        mvprintw(winHeight / 2, winWidth / 2 - 19, "Client started - Connecting to server");
    }
    refresh();
}

void handleInputs() {
    while (true) {
        int ch = getch();
        switch (ch) {
            case ERR:
                return;
            case KEY_RESIZE:
                resizeterm(winHeight, winWidth);
                break;
            case KEY_LEFT:
                if (playerPos.x - paddleSize / 2 > 1)
                    playerPos.x--;
                break;
            case KEY_RIGHT:
                if (playerPos.x + paddleSize / 2 < winWidth - 2)
                    playerPos.x++;
                break;
            default:
                break;
        }
    }
}

void networkReceive() {
    std::string msg;
    while (true) {
        if (!gameInProgress) {
            return;
        }

        msg = network->receive();
        if (!msg.empty()) {
            opponentPos.x = winWidth - std::stoi(msg);
        }
    }
}