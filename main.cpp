#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"

std::vector<Entity> Init();

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML", sf::Style::Close, settings);
    sf::Clock clock;

    auto objs = Init();

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        auto elapsedSec = clock.restart().asSeconds();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        for(auto &obj : objs) {
            obj.Update(elapsedSec);
        }

        window.clear();

        for(auto &obj : objs) {
            auto cShape = obj.Draw();
            window.draw(*cShape);
        }

        window.display();
    }

    return 0;
}

std::vector<Entity> Init() {
    std::vector<Entity> res;

    Entity wo(100, 100);
    res.push_back(wo);

    return res;
}
