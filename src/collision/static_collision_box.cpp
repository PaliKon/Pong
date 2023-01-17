#include <algorithm>
#include "static_collision_box.h"

static_collision_box::static_collision_box(glm::ivec2 cornerA, glm::ivec2 cornerB,
                                           bool bounceHorizontal, bool bounceVertical)
        : collision_object(bounceHorizontal, bounceVertical) {
    this->cornerA = glm::ivec2(std::min(cornerA.x, cornerB.x), std::min(cornerA.y, cornerB.y));
    this->cornerB = glm::ivec2(std::max(cornerA.x, cornerB.x), std::max(cornerA.y, cornerB.y));
}

bool static_collision_box::willCollide(glm::ivec2 position, glm::ivec2 velocity) {
    glm::ivec2 nextPos = position + velocity;
    return nextPos.x >= cornerA.x && nextPos.x <= cornerB.x && nextPos.y >= cornerA.y && nextPos.y <= cornerB.y;
}
