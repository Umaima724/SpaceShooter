#include "Bullet.hpp"

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