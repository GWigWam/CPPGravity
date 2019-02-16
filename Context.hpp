#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Context {

    public:
        void init(unsigned int noObjs, unsigned long size);
        void update(const float& elapsedSec);
        void draw(sf::RenderWindow& window, float scale);

        std::vector<Entity> Entities;
};

#endif
