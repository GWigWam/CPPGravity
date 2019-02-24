#include "Entity.hpp"
#include "Context.hpp"
#include "VMath.cpp"

const float c_kilo = 1000;
const float c_mega = 1000000;
const float c_giga = 1000000000;
const float c_tera = 1000000000000;
const float c_peta = 1000000000000000;

// const G / k(ilo)g / m / s = 6.674e-11
const float G_kg_m_s = 0.00000000006674;

// const G / P(eta)g / m / s
const float G_Pg_m_s = G_kg_m_s * (c_tera * c_tera);

//const G / P(eta)g / M(ega)m / s
const float G_Pg_Mm_s = G_Pg_m_s / (c_mega * c_mega);

EntityState::EntityState() { }

EntityState::EntityState(float xp, float yp, float xv, float yv, float mass) : position(xp, yp), velocity(xv, yv), detlaV(0, 0), mass(mass) { }

Entity::Entity(float xp, float yp, float xv, float yv, float mass, const sf::Color& color) :
    shape(5),
    state1(std::make_unique<EntityState>(xp, yp, xv, yv, mass)),
    state2(std::make_unique<EntityState>(xp, yp, xv, yv, mass)) {
    state = state1.get();
    nextState = state2.get();
    shape.setFillColor(color);
}

Entity::Entity(Entity&& other) :
    shape(std::move(other.shape)),
    state1(std::move(other.state1)),
    state2(std::move(other.state2)) {
    auto isInState1 = other.state == state1.get();
    state = isInState1 ? state1.get() : state2.get();
    nextState = isInState1 ? state1.get() : state2.get();
}

void Entity::update(const float& elapsedSec, std::vector<Entity>::iterator from, std::vector<Entity>::const_iterator to) {
    for(auto ent = from; ent != to; ent++) {
        float m = this->state->mass * ent->state->mass;
        float rsqr = VMath::distanceSqr(this->state->position, ent->state->position);
        float f = G_Pg_Mm_s * (m / rsqr); // Force in N (newtons) (kg/m/s)

        apply_force(f, ent->state->position);
        ent->apply_force(f, this->state->position);
    }

    sf::Vector2f deltaVt = this->nextState->detlaV * elapsedSec;
    this->nextState->velocity = this->state->velocity + deltaVt;
    
    sf::Vector2f deltaXY = this->nextState->velocity * elapsedSec;    
    this->nextState->position = this->state->position + deltaXY;
}

void Entity::apply_force(float force, sf::Vector2f target) {
    float a = force / c_tera / this->state->mass; // Acceleration in m/s
    float a_Mm_s = a / c_mega; // Acceleration in Mm/s

    auto direction = VMath::normalise(target - this->state->position);

    this->nextState->detlaV += direction * a_Mm_s;
}

void Entity::swap() {
    EntityState* s_ptr = this->state;
    this->state = this->nextState;
    this->nextState = s_ptr;

    this->nextState->detlaV = sf::Vector2f(0, 0);
}

sf::Drawable& Entity::draw(float scale, float lag) {
    auto drawAt = (this->state->position + (this->state->velocity * lag)) * scale;
    this->shape.setPosition(drawAt);
    return this->shape;
}

bool Entity::operator==(const Entity& other) const {
    return this == std::addressof(other);
}
bool Entity::operator!=(const Entity& other) const {
    return !(this->operator==(other));
}
