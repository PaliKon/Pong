#ifndef GAME_DYNAMIC_COLLISION_BOX_H
#define GAME_DYNAMIC_COLLISION_BOX_H


#include <functional>
#include "collision_object.h"

class dynamic_collision_box : public collision_object {
private:
    std::function<glm::ivec2(void)> supplierCornerA;
    std::function<glm::ivec2(void)> supplierCornerB;
public:
    dynamic_collision_box(std::function<glm::ivec2(void)> supplierCornerA,
                          std::function<glm::ivec2(void)> supplierCornerB,
                          bool bounceHorizontal, bool bounceVertical1);

    bool willCollide(glm::ivec2 position, glm::ivec2 velocity) override;
};


#endif //GAME_DYNAMIC_COLLISION_BOX_H
