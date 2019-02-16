#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Context {

    public:
        void init(int noObjs, int xMax, int yMax);
        void update(const float& elapsedSec);
        void draw(sf::RenderWindow& window);

        std::vector<Entity> Entities;
};

#endif
