#ifndef ENTITY
#define ENTITY

#include <SFML/Graphics.hpp>

class Entity {
    public:
    Entity(float xp, float yp);

    void update(const float& elapsedSec);
    sf::Drawable* draw();

    private:
    float xp;
    float yp;
    sf::CircleShape shape;
};

#endif
