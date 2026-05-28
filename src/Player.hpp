#pragma once
#include "Entity.hpp"

class Player : public Entity {
public:
    Player();
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const;
    
private:
    sf::RectangleShape shape;
    float speed;
};