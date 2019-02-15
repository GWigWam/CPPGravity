#include "Context.hpp"

void Context::init() {
    Entities.push_back(Entity(10, 100, 0.002, 0.001, 100));
}

void Context::update(const float& elapsedSec) {
    for(auto &ent : Entities) {
        ent.update(elapsedSec, *this);
    }
    for(auto &ent : Entities) {
        ent.swap();
    }
}

void Context::draw(sf::RenderWindow& window) {
    for(auto &ent : Entities) {
        window.draw(ent.draw());
    }
}
