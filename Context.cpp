#include "Context.hpp"

#include <random>

void Context::init(unsigned int noObjs, unsigned long size, float timeFactor) {
    this->timeFactor = timeFactor;
    /*std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<> dist(0, size);

    for(int i = 0; i < noObjs; i++) {
        int x = dist(generator);
        int y = dist(generator);
        Entities.push_back(Entity(x, y, 0, 0, 1000000000));
    }*/

    Entities.push_back(Entity(500000, 500000, 0, 0, 1988500000000000000/*000000000000*/));                // sun      1.9885e30kg
    Entities.push_back(Entity(500000 - 147800/*000000*/, 500000, 0, 0, 5972300000000/*000000000000*/));   // earth    5.9723e24kg, 1.478e11m dist, 30140m/s
}

void Context::update(const float& elapsedSec) {
    auto time = elapsedSec * this->timeFactor;
    for(auto &ent : Entities) {
        ent.update(time, *this);
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
