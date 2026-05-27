#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual ~Entity() = default;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual bool isAlive() const { return alive; }
    virtual sf::FloatRect getBounds() const = 0;
    
    void destroy() { alive = false; }
    
protected:
    bool alive = true;
};