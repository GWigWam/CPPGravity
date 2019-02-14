#ifndef ENTITY
#define ENTITY

#include <SFML/Graphics.hpp>

class Entity {
    public:
    Entity(float xp, float yp);

    void Update(const float& elapsedSec);
    sf::Drawable* Draw();

    private:
    float xp;
    float yp;
    sf::CircleShape shape;
};

#endif
