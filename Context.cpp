#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Context {

public:
    void Init() {
        Entity wo(100, 100);
        Entities.push_back(wo);
    }

    void Update(const float& elapsedSec) {
        for(auto &ent : Entities) {
            ent.Update(elapsedSec);
        }
    }

    template<typename DrawFunc>
    void Draw(DrawFunc&& draw) {
        for(auto &ent : Entities) {
            draw(*ent.Draw());
        }
    }

    std::vector<Entity> Entities;
};
