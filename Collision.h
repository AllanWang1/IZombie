#pragma once

#include <SFML/Graphics.hpp>

namespace izombie
{
    class Collision
    {
    public:
        Collision();

        bool Collided(sf::Sprite zombie, sf::Sprite sprite);

    };
}
