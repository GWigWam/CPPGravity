#include "Context.hpp"

void Context::init(int noObjs, int xMax, int yMax) {
    for(int i = 0; i < noObjs; i++) {
        int x = rand() % xMax;
        int y = rand() % yMax;
        Entities.push_back(Entity(x, y, 0, 0, 100));
    }
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
