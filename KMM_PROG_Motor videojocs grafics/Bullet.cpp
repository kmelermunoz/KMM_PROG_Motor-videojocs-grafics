#include "Bullet.h"

Bullet::Bullet(float x, float y) : velocity(sf::Vector2f(0.5f, 0)) {
    shape.setPosition(x, y); // Establim la posició inicial de la bala a les coordenades (x, y)
    shape.setRadius(5.f); // Establim el radi de la forma circular de la bala
    shape.setFillColor(sf::Color::Blue); // Establim el color de la bala com a blau
}

void Bullet::update() {
    shape.move(velocity); // Movem la bala segons la seva velocitat
}
