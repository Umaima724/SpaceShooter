#pragma once
#include "Entity.hpp"

class Particle : public Entity {
public:
    Particle(sf::Vector2f pos, sf::Color color, float lifetime);
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override { return {}; }
    
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float lifetime;
    float maxLifetime;
};