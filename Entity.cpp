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

EntityState::EntityState(float xp, float yp, float xv, float yv, float mass) : position(xp, yp), velocity(xv, yv), mass(mass) { }

Entity::Entity(float xp, float yp, float xv, float yv, float mass) :
    shape(5),
    state1(std::make_unique<EntityState>(xp, yp, xv, yv, mass)),
    state2(std::make_unique<EntityState>()) {
    this->state = this->state1.get();
    this->nextState = this->state2.get();
}

void Entity::update(const float& elapsedSec, Context& c) {
    sf::Vector2f acceleration;
    for(auto &ent : c.Entities) {
        if(ent != *this) {
            float m = this->state->mass * ent.state->mass;
            float rsqr = VMath::distanceSqr(this->state->position, ent.state->position);
            float f = G_Pg_Mm_s * (m / rsqr); // Force in N (newtons) (kg/m/s)
            float a = f / c_tera / this->state->mass; // Acceleration in m/s
            float a_Mm_s = a / c_mega; // Acceleration in Mm/s

            auto direction = VMath::normalse(ent.state->position - this->state->position);
            acceleration += direction * a_Mm_s;
        }
    }

    sf::Vector2f deltaV = acceleration * elapsedSec;
    this->nextState->velocity = this->state->velocity + deltaV;

    sf::Vector2f deltaXY = this->nextState->velocity * elapsedSec;
    this->nextState->position = this->state->position + deltaXY;
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

bool Entity::operator==(const Entity& other) const {
    return this == std::addressof(other);
}
bool Entity::operator!=(const Entity& other) const {
    return !(this->operator==(other));
}
