#include "Sphere.h"

Sphere::Sphere(sf::Vector2f pos, float r, float m, float b)
    : position(pos), radius(r), mass(m), bounciness(b) {
    velocity = sf::Vector2f(0.f, 0.f);
}
