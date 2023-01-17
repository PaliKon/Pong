#ifndef GAME_COLLISION_OBJECT_H
#define GAME_COLLISION_OBJECT_H


#include "glm/vec2.hpp"

class collision_object {
private:
    bool bounceHorizontal;
    bool bounceVertical;
public:
    collision_object(bool bounceHorizontal, bool bounceVertical);

    virtual bool willCollide(glm::ivec2 position, glm::ivec2 velocity) = 0;

    glm::ivec2 bounce(glm::ivec2 velocity);
};


#endif //GAME_COLLISION_OBJECT_H
