#pragma once
#include "Entity.hpp"
#include "Bullet.hpp"

class Bullet : public Entity {
public:
    Bullet(sf::Vector2f pos);
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;
    
private:
    sf::RectangleShape shape;
    float speed = 500.0f;
};


Bullet::Bullet(sf::Vector2f pos) {
    shape.setSize({6, 18});
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(3, 9);
    shape.setPosition(pos);
}

void Bullet::update(float dt) {
    shape.move(0, -speed * dt);
    if (shape.getPosition().y < -20) alive = false;
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect Bullet::getBounds() const {
    return shape.getGlobalBounds();
}