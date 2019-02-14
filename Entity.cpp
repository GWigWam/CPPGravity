#include "Entity.hpp"
#include "Context.hpp"

Entity::Entity(float xp, float yp) {
    this->xp = xp;
    this->yp = yp;
    this->shape = sf::CircleShape(5);
}

void Entity::update(const float& elapsedSec, Context& c) {
    this->shape.setPosition(xp, yp);
}

sf::Drawable& Entity::draw() {
    return this->shape;
}
