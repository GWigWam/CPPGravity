#include "Context.hpp"

#include <random>

void Context::init(unsigned int noObjs, unsigned long size) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<> dist(0, size);

    for(int i = 0; i < noObjs; i++) {
        int x = dist(generator);
        int y = dist(generator);
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

void Context::draw(sf::RenderWindow& window, float scale) {
    for(auto &ent : Entities) {
        window.draw(ent.draw(scale));
    }
}
