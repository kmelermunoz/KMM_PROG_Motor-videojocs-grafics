#include "Player.h"

Player::Player() {
    shape.setSize(sf::Vector2f(50.f, 50.f)); // Establim les dimensions del jugador
    shape.setPosition(400, 550); // Ajustem la posició inicial del jugador
    shape.setFillColor(sf::Color::Red); // Establim el color del jugador com a vermell
}

void Player::shoot() {
    bullets.push_back(Bullet(shape.getPosition().x + shape.getSize().x / 2 - 2.5f, shape.getPosition().y)); // Disparem una nova bala des de la posició del jugador
}

void Player::update() {
    for (int i = 0; i < bullets.size(); ++i) {
        bullets[i].update(); // Actualitzem cada bala
        if (bullets[i].shape.getPosition().x > 800) { // Si la bala surt de la finestra, l'eliminem
            bullets.erase(bullets.begin() + i);
            --i;
        }
    }
}
