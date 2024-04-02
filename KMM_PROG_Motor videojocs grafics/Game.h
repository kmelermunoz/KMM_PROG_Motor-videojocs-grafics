// Game.h
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h" // Afegim Bullet.h per utilitzar la classe Bullet
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow mWindow;
    Player mPlayer;
    std::vector<Enemy> mEnemies;
    std::vector<Bullet> mBullets; // Vector de balles del jugador
    bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight;
    int mScore;
    int mTime = 0;
    bool mGameOver;

    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void updateBullets(sf::Time deltaTime); // Afegim una funció per actualitzar les balles
    void updateEnemies(sf::Time deltaTime);
    void checkCollisions();
};
