#include "Particle.hpp"

Particle::Particle(sf::Vector2f pos, sf::Color color, float life) 
    : lifetime(life), maxLifetime(life) {
    shape.setRadius(3 + rand() % 4);
    shape.setFillColor(color);
    shape.setPosition(pos);
    
    float angle = (rand() % 360) * 3.14159f / 180.f;
    float speed = 50 + rand() % 150;
    velocity = {std::cos(angle) * speed, std::sin(angle) * speed};
}

void Particle::update(float dt) {
    shape.move(velocity * dt);
    lifetime -= dt;
    
    // Fade out
    sf::Color c = shape.getFillColor();
    c.a = static_cast<sf::Uint8>(255 * (lifetime / maxLifetime));
    shape.setFillColor(c);
    
    if (lifetime <= 0) alive = false;
}

void Particle::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}