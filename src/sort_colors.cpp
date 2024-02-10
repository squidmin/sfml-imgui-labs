#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <vector>
#include <algorithm>

struct ColorTriplet {
    int r, g, b;
};

std::vector<ColorTriplet> generateRandomTriplets(int size) {
    std::vector<ColorTriplet> triplets(size);
    for (size_t i = 0; i < triplets.size(); ++i) {
        triplets[i].r = rand() % 256;
        triplets[i].g = rand() % 256;
        triplets[i].b = rand() % 256;
    }
    return triplets;
}

void drawTriplets(sf::RenderWindow &window, const std::vector<ColorTriplet> &triplets) {
    float width = window.getSize().x / static_cast<float>(triplets.size());
    for (size_t i = 0; i < triplets.size(); ++i) {
        sf::RectangleShape rect(sf::Vector2f(width, window.getSize().y));
        rect.setPosition(i * width, 0);
        rect.setFillColor(sf::Color(triplets[i].r, triplets[i].g, triplets[i].b));
        window.draw(rect);
    }
}

int dominantColor(const ColorTriplet &c) {
    if (c.r >= c.g && c.r >= c.b) { return 0; } // Red is dominant
    if (c.g >= c.r && c.g >= c.b) { return 1; } // Green is dominant
    return 2; // Blue is dominant
}

bool incrementalSortColors(std::vector<ColorTriplet> &colors, size_t &red, size_t &green, size_t &blue) {
    if (green <= blue) {
        if (dominantColor(colors[green]) == 0) {
            std::swap(colors[red], colors[green]);
            green++;
            red++;
        }
        else if (dominantColor(colors[green]) == 1) {
            green++;
        }
        else {
            std::swap(colors[green], colors[blue]);
            blue--;
        }
        return true; // Indicate that sorting is still in progress
    }
    return false; // Sorting is complete
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "Color Sorting");
    ImGui::SFML::Init(window);

    auto triplets = generateRandomTriplets(700);
    bool sorting = false;
    size_t red = 0, green = 0, blue = triplets.size() - 1;
    int delay = 1000; // Delay in milliseconds
    sf::Clock sortTimer;

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Control Panel");
        ImGui::SliderInt("Delay", &delay, 0, 2000);
        if (ImGui::Button("Sort")) {
            sorting = true;
            red = 0;
            green = 0;
            blue = triplets.size() - 1;
            sortTimer.restart();
        }
        ImGui::End();

        if (sorting && sortTimer.getElapsedTime().asMilliseconds() >= delay) {
            sorting = incrementalSortColors(triplets, red, green, blue);
            sortTimer.restart();
        }

        window.clear();
        drawTriplets(window, triplets);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
