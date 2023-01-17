#include "collision_object.h"

collision_object::collision_object(bool bounceHorizontal, bool bounceVertical) {
    this->bounceHorizontal = bounceHorizontal;
    this->bounceVertical = bounceVertical;
}

glm::ivec2 collision_object::bounce(glm::ivec2 velocity) {
    if (bounceHorizontal) {
        velocity.x *= -1;
    }
    if (bounceVertical) {
        velocity.y *= -1;
    }

    return velocity;
}
