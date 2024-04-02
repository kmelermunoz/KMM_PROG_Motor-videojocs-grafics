#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include <cstdlib> // Per rand() i srand()
#include <ctime> // Per time()
#include <SFML/Graphics.hpp>

// Constructor de la classe Game
Game::Game() : mWindow(sf::VideoMode(640, 480), "SFML Game"), mPlayer(), mIsMovingUp(false), mIsMovingDown(false), mIsMovingLeft(false), mIsMovingRight(false), mScore(0), mGameOver(false) {
    srand(time(NULL)); // Inicialitzar generador de nombres aleatoris
    mPlayer.shape.setPosition(320.f - mPlayer.shape.getSize().x / 2, 480.f - mPlayer.shape.getSize().y - 10.f); // Col·locar el jugador a la part inferior centrada
}

// Bucle principal del joc
void Game::run() {
    sf::Clock clock;
    while (mWindow.isOpen() && !mGameOver) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        checkCollisions();
        render();
    }
}

// Processa els esdeveniments de la finestra
void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

// Actualitza l'estat del joc
void Game::update(sf::Time deltaTime) {
    // Actualització del jugador
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp) movement.y -= 1.f;
    if (mIsMovingDown) movement.y += 1.f;
    if (mIsMovingLeft) movement.x -= 1.f;
    if (mIsMovingRight) movement.x += 1.f;
    mPlayer.shape.move(movement * 100.f * deltaTime.asSeconds());

    // Actualització de bales
    for (auto& bullet : mPlayer.bullets) {
        bullet.update();
    }

    // Eliminar bales fora de pantalla
    mPlayer.bullets.erase(std::remove_if(mPlayer.bullets.begin(), mPlayer.bullets.end(), [this](const Bullet& b) {
        return b.shape.getPosition().y < 0;
        }), mPlayer.bullets.end());

    // Generar enemics
    if (mTime > 10000) {
        mEnemies.push_back(Enemy(mWindow.getSize().x, rand() % mWindow.getSize().y));
        mTime = 0;
    }
    else {
        mTime++;
    }

    // Actualitzar enemics
    for (auto& enemy : mEnemies) {
        enemy.update();
    }

    // Eliminar enemics que han sortit de pantalla
    mEnemies.erase(std::remove_if(mEnemies.begin(), mEnemies.end(), [this](const Enemy& e) {
        return e.shape.getPosition().y > mWindow.getSize().y;
        }), mEnemies.end());
}

// Renderitza els elements del joc a la finestra
void Game::render() {
    mWindow.clear();
    mWindow.draw(mPlayer.shape);
    for (auto& bullet : mPlayer.bullets) {
        mWindow.draw(bullet.shape);
    }
    for (auto& enemy : mEnemies) {
        mWindow.draw(enemy.shape);
    }
    mWindow.display();
}

// Gestiona la entrada del jugador
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W) mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S) mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::Space && isPressed) mPlayer.shoot();
}

// Comprova les col·lisions entre els elements del joc
void Game::checkCollisions() {
    // Comprova col·lisions entre balles del jugador i enemics
    for (auto bulletIt = mPlayer.bullets.begin(); bulletIt != mPlayer.bullets.end();) {
        bool bulletRemoved = false;
        for (auto enemyIt = mEnemies.begin(); enemyIt != mEnemies.end() && !bulletRemoved;) {
            if (bulletIt->shape.getGlobalBounds().intersects(enemyIt->shape.getGlobalBounds())) {
                bulletIt = mPlayer.bullets.erase(bulletIt);
                enemyIt = mEnemies.erase(enemyIt);
                mScore += 1; // Augmenta la puntuació
                bulletRemoved = true;
            }
            else {
                ++enemyIt;
            }
        }
        if (!bulletRemoved) ++bulletIt;
    }

    // Comprova si algun enemic ha arribat al final de la pantalla
    for (auto& enemy : mEnemies) {
        if (enemy.shape.getPosition().y + enemy.shape.getSize().y >= mWindow.getSize().y) {
            mGameOver = true;
            break;
        }
    }
}
