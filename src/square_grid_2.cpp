#include <complex>
#include "SFML/Graphics.hpp"
#include "imgui-SFML.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 1080), "Square Grid 1");
    window.setFramerateLimit(60);

    // Calculate the size of each square
    unsigned int squareSize = window.getSize().x / 20;
    unsigned int outlineThickness = 2.0;

    // Create a rectangle shape for each square
    sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
    square.setFillColor(sf::Color::Black);
    square.setOutlineColor(sf::Color::White);
    square.setOutlineThickness(outlineThickness);

    window.display();

    float rotation = 0;

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event = {};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Draw the grid of squares
        rotation += 3.0;
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                // Set the position of the square
                squareSize = (x + y) + 80 * std::abs(std::sin(deltaClock.getElapsedTime().asSeconds()));
                square.setPosition((window.getSize().x / 2) - 100 + (x / 0.2), (window.getSize().y / 2) - 100 + (y / 0.2));
                square.setRotation(rotation * 0.1 * (float) (x / 3) + (y * 10));
                outlineThickness = (15 * 0.2) * std::abs(std::sin(deltaClock.getElapsedTime().asSeconds())) + 1;
                square.setOutlineThickness(outlineThickness);
                square.setOrigin(sf::Vector2f(0, 0));
                // Draw the square
                window.draw(square);
            }
        }

        window.display();
    }

    return 0;
}