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
    float speed;
    float swayAmplitude;
    float swayFrequency;
    float time;
    float startX;
};