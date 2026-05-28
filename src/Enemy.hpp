#pragma once
#include "Entity.hpp"

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