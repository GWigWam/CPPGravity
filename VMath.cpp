#include <cmath>
#include <SFML/Graphics.hpp>

#ifndef VMATH_CPP
#define VMATH_CPP

namespace VMath {
    template<typename T>
    inline sf::Vector2<T> normalise(sf::Vector2<T> source)
    {
        T len = std::hypot(source.x, source.y);
        if (len != 0) {
            source /= len;
        }
        return source;
    }

    template<typename T>
    inline T distance(sf::Vector2<T> v1, sf::Vector2<T> v2)
    {
        sf::Vector2<T> sub = v1 - v2;
        return std::hypot(sub.x, sub.y);
    }

    template<typename T>
    inline T distanceSqr(sf::Vector2<T> v1, sf::Vector2<T> v2)
    {
        sf::Vector2<T> sub = v1 - v2;
        return (sub.x * sub.x) + (sub.y * sub.y);
    }

    template<typename T>
    inline T magnitude(sf::Vector2<T> v)
    {
        return std::hypot(v.x, v.y);
    }
}

#endif
