#include <iostream>
#include <SFML/Graphics.hpp>

#include "Context.hpp"

#define SCREEN_SIZE 900

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Gravity", sf::Style::Close, settings);
    sf::Clock clock;

    unsigned long wSizeMm = 1000000;
    float scale = SCREEN_SIZE / (float)wSizeMm;

    Context context;
    context.init(100, wSizeMm, 24 * 60 * 60);

    const float S_PER_UPDATE = 1.0 / 60.0;
    float lag = 0;
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

        float elapsedSec = clock.restart().asSeconds();
        lag += elapsedSec;

        while(lag >= S_PER_UPDATE) {
            context.update(S_PER_UPDATE);
            lag -= S_PER_UPDATE;
        }

        window.clear();
        context.draw(window, scale);
        window.display();
    }

    return 0;
}
