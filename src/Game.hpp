#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Particle.hpp"

class Game {
public:
    Game();
    void run();
    
private:
    void processEvents();
    void update(float dt);
    void render();
    void spawnEnemy();
    void checkCollisions();
    void spawnExplosion(sf::Vector2f pos, sf::Color color, int count);
    
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Text restartText;
    
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<<Enemy>> enemies;
    std::vector<std::unique_ptr<<Particle>> particles;
    
    float spawnTimer;
    float spawnInterval;
    int score;
    bool gameOver;
    float screenShake;
};