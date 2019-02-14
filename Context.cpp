#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Context {

public:
    void init() {
        Entity wo(100, 100);
        Entities.push_back(wo);
    }

    void update(const float& elapsedSec) {
        for(auto &ent : Entities) {
            ent.update(elapsedSec);
        }
    }

    template<typename DrawFunc>
    void draw(DrawFunc&& draw) {
        for(auto &ent : Entities) {
            draw(*ent.draw());
        }
    }

    std::vector<Entity> Entities;
};
