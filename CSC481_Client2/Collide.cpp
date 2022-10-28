#include "Collide.h"

bool Collide::collision(GameObject* go, GameObject* go2) {
    if (go->getShape().getGlobalBounds().intersects(go2->getShape().getGlobalBounds())) {
        return true;
    }
    return false;
}