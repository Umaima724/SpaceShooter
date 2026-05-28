#pragma once
#include <SFML/Graphics.hpp>

inline sf::Vector2f getCenter(const sf::FloatRect& rect) {
    return {rect.left + rect.width / 2.f, rect.top + rect.height / 2.f};
}