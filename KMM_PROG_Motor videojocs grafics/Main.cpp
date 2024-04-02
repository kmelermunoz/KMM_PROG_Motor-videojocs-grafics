#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Enemy.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game");
    window.setFramerateLimit(60);

    Player player;
    std::vector<Enemy> enemies;

    srand(static_cast<unsigned>(time(NULL)));

    float spawnCounter = 0;
    int score = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    player.shoot();
                }
            }
        }