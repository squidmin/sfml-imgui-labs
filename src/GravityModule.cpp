#include "GravityModule.h"

// Gravity constant definition
const sf::Vector2f GravityModule::GRAVITY = sf::Vector2f(0.f, 9.81f); // Adjust based on your simulation scale

void GravityModule::updateSphere(Sphere &sphere, float deltaTime) {
    // Apply gravity to velocity
    sphere.velocity += GravityModule::GRAVITY * deltaTime;

    // Update position based on velocity
    sphere.position += sphere.velocity * deltaTime;

    // Handle ground collision
    float groundLevel = 600.f; // Assuming ground is at y = 600
    if (sphere.position.y + sphere.radius >= groundLevel) {
        sphere.position.y = groundLevel - sphere.radius;
        sphere.velocity.y *= -sphere.bounciness;
    }
}
