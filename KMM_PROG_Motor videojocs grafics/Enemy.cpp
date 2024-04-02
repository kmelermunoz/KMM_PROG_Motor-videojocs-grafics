#include "Enemy.h"

Enemy::Enemy(float x, float y) {
    shape.setPosition(x, y); // Establim la posició inicial de l'enemic
    shape.setSize(sf::Vector2f(20.f, 20.f)); // Establim les dimensions de l'enemic
    shape.setFillColor(sf::Color::Yellow); // Establim el color de l'enemic com a groc
}

void Enemy::update() {
    shape.move(-0.1f, 0); // Movem l'enemic cap a l'esquerra
}
