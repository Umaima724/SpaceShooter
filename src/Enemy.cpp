#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(sf::Vector2f pos) {
    shape.setRadius(20);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(20, 20);
    shape.setPosition(pos);
    startX = pos.x;
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