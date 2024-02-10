#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "GravityModule.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Gravity Simulation");
    ImGui::SFML::Init(window);

    // Animation speed control variable
    float animationSpeed = 1.0f;

    // First sphere
    Sphere sphere1(sf::Vector2f(100.f, 50.f), 20.f, 1.f, 0.7f); // Example sphere
    // Second sphere with different height and size
    Sphere sphere2(sf::Vector2f(200.f, 100.f), 30.f, 1.f, 0.6f); // Different starting height and size
    GravityModule gravityModule;

    sf::Clock deltaClock; // For tracking the time between frames

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Time dt = deltaClock.restart(); // Get the time since last frame

        ImGui::SFML::Update(window, dt);

        // Set ImGui window size and add a slider for animation speed
        ImGui::SetNextWindowSize(ImVec2(300, 100)); // Set the ImGui window size
        ImGui::Begin("Animation Controls");
        ImGui::SliderFloat("Speed", &animationSpeed, 0.0f, 5.0f, "Speed = %.3f"); // Max speed set to 5.0
        ImGui::End();
        
        // Update the sphere with scaled delta time
        gravityModule.updateSphere(sphere1, dt.asSeconds() * animationSpeed);
        gravityModule.updateSphere(sphere2, dt.asSeconds() * animationSpeed);

        // Clear the window with a background color
        window.clear(sf::Color(150, 150, 150)); // Light gray background

        // Draw the first sphere
        sf::CircleShape sphereShape1(sphere1.radius);
        sphereShape1.setPosition(sphere1.position);
        sphereShape1.setFillColor(sf::Color::Blue);
        window.draw(sphereShape1);

        // Draw the second sphere
        sf::CircleShape sphereShape2(sphere2.radius);
        sphereShape2.setPosition(sphere2.position);
        sphereShape2.setFillColor(sf::Color::Green); // Different color for the second sphere
        window.draw(sphereShape2);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
