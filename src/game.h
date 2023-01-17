#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <glm/vec2.hpp>
#include "network/network_object.h"

int launch(network_object *net);

void networkReceive();

void initScreen();

void init();

void initCollisionObjects();

void update();

void updateBall();

void checkResult();

void handleInputs();

void render();

void renderBall();

void renderPaddle(glm::ivec2 &pos);

void renderGameOver();

void renderConnectionScreen();

#endif //GAME_GAME_H
