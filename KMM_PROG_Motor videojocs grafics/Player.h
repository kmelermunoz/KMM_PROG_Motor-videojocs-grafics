#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"

class Player {
public:
    sf::RectangleShape shape; // Forma rectangular que representa el jugador
    std::vector<Bullet> bullets; // Vector de les bales disparades pel jugador

    Player(); // Constructor del jugador
    void shoot(); // Funció per disparar una nova bala
    void update(); // Funció per actualitzar l'estat del jugador
};

#endif
