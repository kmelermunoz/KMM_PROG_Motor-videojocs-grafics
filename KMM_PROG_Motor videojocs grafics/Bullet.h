#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
public:
    sf::CircleShape shape; // Forma circular que representa la bala
    sf::Vector2f velocity; // Velocitat de la bala

    Bullet(float x, float y); // Constructor de la bala, amb les coordenades (x, y)
    void update(); // Funció per actualitzar la posició de la bala
};

#endif
