#include <iostream>
#include <SFML/Graphics.hpp>

#include "Context.hpp"

#define SCREEN_SIZE 900

void draw_counters(sf::RenderWindow& window, const sf::Font& font, const int& frames, const int& updates, const bool& warn);

int main() {
    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        std::cout << "Failed to load font";
        return 1;
    }

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Gravity", sf::Style::Close, settings);
    sf::Clock clock;

    unsigned long wSizeMm = 1000000;
    float scale = SCREEN_SIZE / (float)wSizeMm;

    Context context;
    context.init(100, wSizeMm, 24 * 60 * 60);

    const int UPD_PER_SEC = 60;
    const float S_PER_UPDATE = 1.0 / UPD_PER_SEC;
    float lag = 0;
    int c_frames, frames, c_updates, updates;
    float secCnr;
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
        secCnr += elapsedSec;
        if(secCnr >= 1) {
            frames = c_frames;
            updates = c_updates;
            secCnr = 0;
            c_frames = 0;
            c_updates = 0;

            if(frames == 1) { // Skip a few updates to avoid lag-spiral if FPS = 1
                lag = S_PER_UPDATE;
            }
        }

        while(lag >= S_PER_UPDATE) {
            context.update(S_PER_UPDATE);
            lag -= S_PER_UPDATE;
            c_updates++;
        }

        window.clear();
        context.draw(window, scale, lag);
        draw_counters(window, font, frames, updates, updates < UPD_PER_SEC || frames == 1);
        window.display();
        c_frames++;
    }

    return 0;
}

void draw_counters(sf::RenderWindow& window, const sf::Font& font, const int& frames, const int& updates, const bool& warn) {
    sf::Text t;
    t.setFont(font);
    t.setString(std::to_string(frames) + "/" + std::to_string(updates));
    t.setFillColor(warn ? sf::Color::Red : sf::Color::White);
    window.draw(t);
}
