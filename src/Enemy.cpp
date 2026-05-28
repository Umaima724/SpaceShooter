#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(sf::Vector2f pos) {
    shape.setRadius(20);
    shape.setFillColor(sf::Color::Red);
    shape.setOutlineColor(sf::Color(200, 50, 50));
    shape.setOutlineThickness(2);
    shape.setOrigin(20, 20);
    shape.setPosition(pos);
    startX = pos.x;
    speed = 150.0f;
    swayAmplitude = 60.0f;
    swayFrequency = 2.5f;
    time = 0;
}

void Enemy::update(float dt) {
    time += dt;
    float sway = std::sin(time * swayFrequency) * swayAmplitude;
    shape.setPosition(startX + sway, shape.getPosition().y + speed * dt);
    
    if (shape.getPosition().y > 620) alive = false;
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect Enemy::getBounds() const {
    return shape.getGlobalBounds();
}