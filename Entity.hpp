#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Context;

struct EntityState {
    public:
        EntityState();
        EntityState(float xp, float yp, float xv, float yv, float mass);
        sf::Vector2f position;
        sf::Vector2f velocity;
        float mass;
};

class Entity {
    public:
    Entity(float xp, float yp, float xv, float yv, float mass);

    void update(const float& elapsedSec, Context& c);
    void swap();
    sf::Drawable& draw(float scale);

    EntityState* state;

    bool operator==(const Entity& b) const;
    bool operator!=(const Entity& b) const;

    private:
    sf::CircleShape shape;
    EntityState* nextState;
    std::unique_ptr<EntityState> state1;
    std::unique_ptr<EntityState> state2;
};

#endif
