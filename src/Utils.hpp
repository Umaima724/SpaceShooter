#pragma once
#include <SFML/Graphics.hpp>

// Helper to get center of FloatRect
inline sf::Vector2f operator|(const sf::FloatRect& rect, int) {
    return {rect.left + rect.width / 2.f, rect.top + rect.height / 2.f};
}

// Extension to FloatRect for center access
namespace sf {
    inline Vector2f FloatRect::getCenter() const {
        return {left + width / 2.f, top + height / 2.f};
    }
}