#include <iostream>
#include <SFML/Graphics.hpp>

#include "Context.hpp"

#define SCREEN_SIZE 900

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Gravity", sf::Style::Close, settings);
    sf::Clock clock;

    unsigned long wSizeMm = 4500000;
    float scale = SCREEN_SIZE / (float)wSizeMm;

    Context context;
    context.init(100, wSizeMm);

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
        context.draw(window, scale);
        window.display();
    }

    return 0;
}
