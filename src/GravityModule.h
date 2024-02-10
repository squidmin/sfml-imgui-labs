#ifndef GRAVITY_MODULE_H
#define GRAVITY_MODULE_H

#include <SFML/Graphics.hpp>
#include "Sphere.h"

class GravityModule {
public:
    static const sf::Vector2f GRAVITY; // Adjust the value to suit the scale of your simulation
    void updateSphere(Sphere &sphere, float deltaTime);
};

#endif // GRAVITY_MODULE_H
