#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
    sf::RectangleShape shape; // Forma rectangular que representa l'enemic

    Enemy(float x, float y); // Constructor de l'enemic, amb les coordenades (x, y)
    void update(); // Funció per actualitzar l'estat de l'enemic
};

#endif
