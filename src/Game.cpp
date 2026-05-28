#include "Game.hpp"
#include <algorithm>

Game::Game() 
    : window(sf::VideoMode(800, 600), "Space Shooter - SFML", sf::Style::Close),
      spawnTimer(0), spawnInterval(1.5f), score(0), gameOver(false), screenShake(0) {
    
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    
    player = std::make_unique<Player>();
    
    if (!font.loadFromFile("assets/arial.ttf")) {
        // Fallback: try system font paths
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    }
    
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    sf::FloatRect goBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(goBounds.width / 2, goBounds.height / 2);
    gameOverText.setPosition(400, 250);
    
    restartText.setFont(font);
    restartText.setString("Press R to Restart");
    restartText.setCharacterSize(24);
    restartText.setFillColor(sf::Color::White);
    sf::FloatRect rBounds = restartText.getLocalBounds();
    restartText.setOrigin(rBounds.width / 2, rBounds.height / 2);
    restartText.setPosition(400, 320);
}

void Game::run() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        dt = std::min(dt, 0.05f);
        
        processEvents();
        
        if (!gameOver) {
            update(dt);
        } else {
            // Still update particles during game over
            for (auto& p : particles) p->update(dt);
            particles.erase(std::remove_if(particles.begin(), particles.end(),
                [](auto& p) { return !p->isAlive(); }), particles.end());
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
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
                
            if (event.key.code == sf::Keyboard::Space && !gameOver) {
                bullets.push_back(std::make_unique<Bullet>(
                    player->getPosition() - sf::Vector2f(0, 25)
                ));
            }
            
            if (event.key.code == sf::Keyboard::R && gameOver) {
                player = std::make_unique<Player>();
                enemies.clear();
                bullets.clear();
                particles.clear();
                score = 0;
                gameOver = false;
                spawnTimer = 0;
                spawnInterval = 1.5f;
                screenShake = 0;
            }
        }
    }
}

void Game::update(float dt) {
    player->update(dt);
    
    for (auto& b : bullets) b->update(dt);
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](auto& b) { return !b->isAlive(); }), bullets.end());
    
    spawnTimer += dt;
    if (spawnTimer >= spawnInterval) {
        spawnEnemy();
        spawnTimer = 0;
        spawnInterval = std::max(0.4f, spawnInterval - 0.03f);
    }
    
    for (auto& e : enemies) e->update(dt);
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](auto& e) { return !e->isAlive(); }), enemies.end());
    
    for (auto& p : particles) p->update(dt);
    particles.erase(std::remove_if(particles.begin(), particles.end(),
        [](auto& p) { return !p->isAlive(); }), particles.end());
    
    checkCollisions();
    
    scoreText.setString("Score: " + std::to_string(score));
    
    if (screenShake > 0) screenShake -= dt * 10;
}

void Game::spawnEnemy() {
    float x = 50 + rand() % 700;
    enemies.push_back(std::make_unique<<Enemy>(sf::Vector2f(x, -30)));
}

void Game::spawnExplosion(sf::Vector2f pos, sf::Color color, int count) {
    for (int i = 0; i < count; ++i) {
        particles.push_back(std::make_unique<<Particle>(
            pos, color, 0.3f + (rand() % 10) / 20.f
        ));
    }
}

void Game::checkCollisions() {
    for (auto& bullet : bullets) {
        for (auto& enemy : enemies) {
            if (bullet->isAlive() && enemy->isAlive() && 
                bullet->getBounds().intersects(enemy->getBounds())) {
                
                bullet->destroy();
                enemy->destroy();
                score += 100;
                screenShake = 1.0f;
                
                spawnExplosion(enemy->getBounds().getCenter(), 
                    sf::Color(255, 100 + rand() % 155, 0), 15);
            }
        }
    }
    
    for (auto& enemy : enemies) {
        if (enemy->isAlive() && player->getBounds().intersects(enemy->getBounds())) {
            gameOver = true;
            screenShake = 2.0f;
            spawnExplosion(player->getPosition(), sf::Color::Cyan, 30);
            spawnExplosion(player->getPosition(), sf::Color::White, 10);
        }
    }
}

void Game::render() {
    window.clear(sf::Color(10, 10, 30));
    
    sf::View view = window.getDefaultView();
    if (screenShake > 0) {
        float offsetX = (rand() % 20 - 10) * screenShake;
        float offsetY = (rand() % 20 - 10) * screenShake;
        view.move(offsetX, offsetY);
    }
    window.setView(view);
    
    for (auto& e : enemies) e->draw(window);
    for (auto& b : bullets) b->draw(window);
    player->draw(window);
    for (auto& p : particles) p->draw(window);
    
    window.setView(window.getDefaultView());
    window.draw(scoreText);
    
    if (gameOver) {
        window.draw(gameOverText);
        window.draw(restartText);
    }
    
    window.display();
}