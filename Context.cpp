#include "Context.hpp"

void Context::init() {
    Entity wo(100, 100);
    Entities.push_back(wo);
}

void Context::update(const float& elapsedSec) {
    for(auto &ent : Entities) {
        ent.update(elapsedSec, *this);
    }
}

void Context::draw(sf::RenderWindow& window) {
    for(auto &ent : Entities) {
        window.draw(ent.draw());
    }
}
