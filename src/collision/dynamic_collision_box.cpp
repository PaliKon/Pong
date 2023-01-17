#include "dynamic_collision_box.h"

dynamic_collision_box::dynamic_collision_box(std::function<glm::ivec2(void)> supplierCornerA,
                                             std::function<glm::ivec2(void)> supplierCornerB,
                                             bool bounceHorizontal, bool bounceVertical)
        : collision_object(bounceHorizontal, bounceVertical) {
    this->supplierCornerA = std::move(supplierCornerA);
    this->supplierCornerB = std::move(supplierCornerB);
}

bool dynamic_collision_box::willCollide(glm::ivec2 position, glm::ivec2 velocity) {
    glm::ivec2 nextPos = position + velocity;
    glm::ivec2 cornerA = this->supplierCornerA();
    glm::ivec2 cornerB = this->supplierCornerB();

    return nextPos.x >= cornerA.x && nextPos.x <= cornerB.x && nextPos.y >= cornerA.y && nextPos.y <= cornerB.y;
}
