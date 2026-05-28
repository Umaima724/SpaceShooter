#include "Game.hpp"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Space Shooter - SFML", sf::Style::Close) {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    
    player = std::make_unique<Player>();
    
    if (font.loadFromFile("assets/arial.ttf")) {
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);
    }
}

void Game::run() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        // Cap delta time to prevent physics explosions on lag
        dt = std::min(dt, 0.05f);
        
        processEvents();
        
        if (!gameOver) {
            update(dt);
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
            
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space && !gameOver) {
                bullets.push_back(std::make_unique<Bullet>(player->getPosition() - sf::Vector2f(0, 25)));
            }
            if (event.key.code == sf::Keyboard::R && gameOver) {
                // Restart
                player = std::make_unique<Player>();
                enemies.clear();
                bullets.clear();
                particles.clear();
                score = 0;
                gameOver = false;
                spawnTimer = 0;
            }
        }
    }
}

void Game::update(float dt) {
    player->update(dt);
    
    // Update bullets
    for (auto& b : bullets) b->update(dt);
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](auto& b) { return !b->isAlive(); }), bullets.end());
    
    // Spawn enemies
    spawnTimer += dt;
    if (spawnTimer >= spawnInterval) {
        spawnEnemy();
        spawnTimer = 0;
        // Increase difficulty
        spawnInterval = std::max(0.5f, spawnInterval - 0.02f);
    }
    
    // Update enemies
    for (auto& e : enemies) e->update(dt);
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](auto& e) { return !e->isAlive(); }), enemies.end());
    
    // Update particles
    for (auto& p : particles) p->update(dt);
    particles.erase(std::remove_if(particles.begin(), particles.end(),
        [](auto& p) { return !p->isAlive(); }), particles.end());
    
    checkCollisions();
    
    scoreText.setString("Score: " + std::to_string(score));
}

void Game::spawnEnemy() {
    float x = 50 + rand() % 700;
    enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(x, -30)));
}

void Game::checkCollisions() {
    // Bullet vs Enemy
    for (auto& bullet : bullets) {
        for (auto& enemy : enemies) {
            if (bullet->isAlive() && enemy->isAlive() && 
                bullet->getBounds().intersects(enemy->getBounds())) {
                
                bullet->destroy();
                enemy->destroy();
                score += 100;
                
                // Explosion particles
                for (int i = 0; i < 15; ++i) {
                    particles.push_back(std::make_unique<Particle>(
                        enemy->getBounds().getCenter(), 
                        sf::Color(255, 100 + rand() % 155, 0), 
                        0.5f + (rand() % 10) / 10.f
                    ));
                }
            }
        }
    }
    
    // Player vs Enemy
    for (auto& enemy : enemies) {
        if (enemy->isAlive() && player->getBounds().intersects(enemy->getBounds())) {
            gameOver = true;
            // Big explosion
            for (int i = 0; i < 30; ++i) {
                particles.push_back(std::make_unique<Particle>(
                    player->getPosition(),
                    sf::Color::Cyan,
                    1.0f
                ));
            }
        }
    }
}

void Game::render() {
    window.clear(sf::Color(10, 10, 30)); // Deep space blue
    
    // Draw entities
    for (auto& e : enemies) e->draw(window);
    for (auto& b : bullets) b->draw(window);
    player->draw(window);
    for (auto& p : particles) p->draw(window);
    
    // UI
    window.draw(scoreText);
    
    if (gameOver) {
        sf::Text overText;
        overText.setFont(font);
        overText.setString("GAME OVER\nPress R to Restart");
        overText.setCharacterSize(40);
        overText.setFillColor(sf::Color::White);
        overText.setOrigin(overText.getLocalBounds().width / 2, overText.getLocalBounds().height / 2);
        overText.setPosition(400, 300);
        window.draw(overText);
    }
    
    window.display();
}