#ifndef SPHERE_H
#define SPHERE_H

#include <SFML/Graphics.hpp>

class Sphere {
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;
    float mass;
    float bounciness;

    Sphere(sf::Vector2f pos, float r, float m, float b);
};

#endif // SPHERE_H
