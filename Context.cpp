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
    auto sun_m = 1988500000000000000.000000000000;                          // 1.9885e30kg
    Entity sun(center, center, 0, 0, sun_m);
    Entities.push_back(std::move(sun));

    auto mer_apo = 69820;
    auto mer_x = center - mer_apo;
    auto mer_apo_spd = 0.03886;
    auto mer_m = 330110000000.0000000000000;                                // 3.3011e23kg
    Entity mercury(mer_x, center, 0, mer_apo_spd, mer_m);
    Entities.push_back(std::move(mercury));

    auto ven_dist = 108208;                                                 // 1.08208e11m
    auto ven_x = center - ven_dist;
    auto ven_spd = 0.03502;                                                 // 35020m/s
    auto ven_m = 486750000000.000000000000;                                 // 4.8675e24kg
    Entity venus(ven_x, center, 0, ven_spd, ven_m);
    Entities.push_back(std::move(venus));

    auto earth_apo = 152100;                                                // 1.496e11m
    auto earth_x = center - earth_apo;
    auto earth_apo_spd = 0.02929;                                           // 30140m/s
    auto earth_m = 5972300000000.000000000000;                              // 5.9723e24kg
    Entity earth(earth_x, center, 0, earth_apo_spd, earth_m);
    Entities.push_back(std::move(earth));

    auto moon_dist = 384.402;                                               // 3.84402e8m
    auto moon_x = earth_x - moon_dist;
    auto moon_spd_e = 0.001022;                                             // 1022m/s
    auto moon_spd = moon_spd_e + earth_apo_spd;
    auto moon_m = 73420000000.000000000000;                                 // 7.342e22kg
    Entity moon(moon_x, center, 0, moon_spd, moon_m);
    Entities.push_back(std::move(moon));

    auto mars_dist = 227939.2;                                              // 2.2793292e11
    auto mars_x = center - mars_dist;
    auto mars_spd = 0.0241;                                                 // 24100m/s
    auto mars_m = 641710000000.000000000000;                                // 6.4171e23kg
    Entity mars(mars_x, center, 0, mars_spd, mars_m);
    Entities.push_back(std::move(mars));

    auto jup_dist = 778570;                                                 // 7.7857e11m
    auto jup_x = center - jup_dist;
    auto jup_spd = 0.01306;                                                 // 13060m/s
    auto jup_m = 1898200000000000.000000000000;                             // 1.8982e27kg
    Entity jupiter(jup_x, center, 0, jup_spd, jup_x);
    Entities.push_back(std::move(jupiter));

    auto sat_dist = 1433530;                                                // 1.43353e12m
    auto sat_x = center - sat_dist;
    auto sat_spd = 0.009680;                                                // 9680m/s
    auto sat_m = 568340000000000.000000000000;                              // 5.6834e26kg
    Entity saturn(sat_x, center, 0, sat_spd, sat_m);
    Entities.push_back(std::move(saturn));

    auto ura_dist = 2872500;                                                // 2.8725e12m
    auto ura_x = center - ura_dist;
    auto ura_spd = 0.0068;                                                  // 6800m/s
    auto ura_m = 86800000000000.000000000000;                               // 8.68e25kg
    Entity uranus(ura_x, center, 0, ura_spd, ura_m);
    Entities.push_back(std::move(uranus));

    auto nep_dist = 4495100;                                                // 4.4951e12m
    auto nep_x = center - nep_dist;
    auto nep_spd = 0.0054;                                                  // 5400m/s
    auto nep_m = 102000000000000.000000000000;                              // 1.02e26kg
    Entity neptune(nep_x, center, 0, nep_spd, nep_m);
    Entities.push_back(std::move(neptune));
}

void Context::update(const float& elapsedSec) {
    auto time = elapsedSec * this->timeFactor;
    for(auto ent = Entities.begin(); ent != Entities.end(); ent++) {
        ent->update(time, ent + 1, Entities.cend());
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
