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

    auto center = size / 2;
    Entities.push_back(Entity(center, center, 0, 0, 1988500000000000000.000000000000));         // sun      1.9885e30kg
    auto earth_apo = 152100;
    auto earth_x = center - earth_apo;
    auto earth_apo_spd = 0.02929;
    Entities.push_back(Entity(earth_x, center, 0, earth_apo_spd, 5972300000000.000000000000));  // earth    5.9723e24kg, 1.496e11m dist,  30140m/s
    auto moon_dist = 384.402;
    auto moon_x = earth_x - moon_dist;
    auto moon_spd_e = 0.001022;
    auto moon_spd = moon_spd_e + earth_apo_spd;
    Entities.push_back(Entity(moon_x, center, 0, moon_spd, 73420000000.000000000000));          // moon     7.342e22kg,  3.84402e8m dist, 1022m/s
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

void Context::draw(sf::RenderWindow& window, float scale, float lag) {
    for(auto &ent : Entities) {
        window.draw(ent.draw(scale, lag * this->timeFactor));
    }
}
