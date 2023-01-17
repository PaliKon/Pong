#ifndef GAME_STATIC_COLLISION_BOX_H
#define GAME_STATIC_COLLISION_BOX_H


#include "collision_object.h"

class static_collision_box : public collision_object {
private:
    glm::ivec2 cornerA;
    glm::ivec2 cornerB;
public:
    static_collision_box(glm::ivec2 cornerA, glm::ivec2 cornerB,
                         bool bounceHorizontal, bool bounceVertical);

    bool willCollide(glm::ivec2 position, glm::ivec2 velocity) override;
};


#endif //GAME_STATIC_COLLISION_BOX_H
