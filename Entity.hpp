#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Context;

class Entity {
    public:
    Entity(float xp, float yp);

    void update(const float& elapsedSec, Context& c);
    sf::Drawable& draw();

    private:
    float xp;
    float yp;
    sf::CircleShape shape;
};

#endif
