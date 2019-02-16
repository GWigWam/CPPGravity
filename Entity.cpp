#include "Entity.hpp"
#include "Context.hpp"

EntityState::EntityState() { }

EntityState::EntityState(float xp, float yp, float xv, float yv, float mass) : position(xp, yp), velocity(xv, yv), mass(mass) { }

Entity::Entity(float xp, float yp, float xv, float yv, float mass) :
    shape(5),
    state1(std::make_unique<EntityState>(xp, yp, xv, yv, mass)),
    state2(std::make_unique<EntityState>()) {
    this->state = this->state1.get();
    this->nextState = this->state2.get();
}

void Entity::update(const float& elapsedSec, Context& c) {
    this->nextState->velocity = this->state->velocity + sf::Vector2f(0, 0);
    this->nextState->position = this->state->position + this->nextState->velocity;
}

void Entity::swap() {
    EntityState* s_ptr = this->state;
    this->state = this->nextState;
    this->nextState = s_ptr;
}

sf::Drawable& Entity::draw(float scale) {
    this->shape.setPosition(this->state->position * scale);
    return this->shape;
}
