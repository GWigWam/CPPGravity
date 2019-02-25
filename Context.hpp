#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "VMath.cpp"

class Context {

    public:
        void init(unsigned int noObjs, unsigned long size, float timeFactor);
        void update(const float& elapsedSec);
        void draw(sf::RenderWindow& window, float scale, float lag);

        std::vector<Entity> Entities;
        float timeFactor;
};

#endif
