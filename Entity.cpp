#include "Entity.hpp"

Entity::Entity(float xp, float yp) {
    this->xp = xp;
    this->yp = yp;
    this->shape = sf::CircleShape(5);
}

void Entity::Update(const float& elapsedSec) {
    this->shape.setPosition(xp, yp);
}

sf::Drawable* Entity::Draw() {
    return &(this->shape);
}
