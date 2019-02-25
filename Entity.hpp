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
        sf::Vector2f detlaV;
        float mass;
};

class Entity {
    public:
    Entity(float xp, float yp, float xv, float yv, float mass, const sf::Color& color = sf::Color::White);
    
    Entity(Entity&& other);
    Entity(const Entity& other) = delete;
    Entity& operator=(const Entity& other) = delete;

    static float calc_force(Entity* e1, Entity* e2);

    void update(const float& elapsedSec);
    sf::Vector2f calc_deltav(float force, sf::Vector2f direction);
    void swap();
    sf::Drawable& draw(float scale, float lag);

    EntityState* state;

    bool operator==(const Entity& b) const;
    bool operator!=(const Entity& b) const;

    private:
    sf::CircleShape shape;
    EntityState* nextState;
    std::unique_ptr<EntityState> state1;
    std::unique_ptr<EntityState> state2;

    void apply_force(float force, sf::Vector2f target);
};

#endif
