#include "Context.hpp"

#include <numeric>

void Context::update(const float& elapsedSec) {
    auto time = elapsedSec * this->timeFactor;

    auto cnt = Entities.size();
    sf::Vector2f deltaVs[cnt][cnt];
    for(int i = 0; i < cnt; ++i) {
        for(int j = i + 1; j < cnt; ++j) {
            auto e1 = &Entities[i];
            auto e2 = &Entities[j];
            float f = Entity::calc_force(e1, e2);

            auto dir = VMath::normalise(e2->state->position - e1->state->position);
            auto dv1 = e1->calc_deltav(f, dir);
            dir *= -1.0f;
            auto dv2 = e2->calc_deltav(f, dir);
            deltaVs[i][j] = dv1;
            deltaVs[j][i] = dv2;
        }
    }

    for(int i = 0; i < cnt; ++i) {
        auto tot = std::accumulate(&deltaVs[i][0], &deltaVs[i][cnt], sf::Vector2f(), [](sf::Vector2f acc, const sf::Vector2f& cur){
            return acc + cur;
        });
        Entities[i].state->detlaV = tot;
    }

    for(auto ent = Entities.begin(); ent != Entities.end(); ent++) {
        ent->update(time);
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
