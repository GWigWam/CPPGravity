#include <iostream>
#include <SFML/Graphics.hpp>

#include "Context.hpp"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML", sf::Style::Close, settings);
    sf::Clock clock;

    Context context;
    context.init(100, 700, 700);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        auto elapsedSec = clock.restart().asSeconds();
        context.update(elapsedSec);

        window.clear();
        context.draw(window);
        window.display();
    }

    return 0;
}
