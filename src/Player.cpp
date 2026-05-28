#include "Player.hpp"
#include <algorithm>

Player::Player() {
    shape.setSize({40, 40});
    shape.setFillColor(sf::Color::Cyan);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2);
    shape.setOrigin(20, 20);
    shape.setPosition(400, 500);
    speed = 350.0f;
}

void Player::update(float dt) {
    sf::Vector2f movement(0, 0);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += 1;
    
    if (movement.x != 0 && movement.y != 0) {
        movement *= 0.707f;
    }
    
    shape.move(movement * speed * dt);
    
    sf::Vector2f pos = shape.getPosition();
    pos.x = std::clamp(pos.x, 20.f, 780.f);
    pos.y = std::clamp(pos.y, 20.f, 580.f);
    shape.setPosition(pos);
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}