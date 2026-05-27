#pragma once
#include "Entity.hpp"

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