#pragma once
#include "Entity.hpp"
#include "Enemy.hpp"
#include <cmath>

class Enemy : public Entity {
public:
    Enemy(sf::Vector2f pos);
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;
    
private:
    sf::CircleShape shape;
    float speed = 150.0f;
    float swayAmplitude = 50.0f;
    float swayFrequency = 2.0f;
    float time = 0;
    float startX;
};

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