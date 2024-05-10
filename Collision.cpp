#include "Collision.h"

namespace izombie
{
    Collision::Collision()
    {

    }

    bool Collision::Collided(sf::Sprite zombie, sf::Sprite sprite)
    {
        bool x = (zombie.getPosition().x - zombie.getGlobalBounds().width/2) <
                 (sprite.getPosition().x + sprite.getGlobalBounds().width/2) &&
                 (zombie.getPosition().x + zombie.getGlobalBounds().width/8) >
                 (sprite.getPosition().x - sprite.getGlobalBounds().width/2);

        bool y = (zombie.getPosition().y + zombie.getGlobalBounds().height/2) >
                 (sprite.getPosition().y - sprite.getGlobalBounds().height/2);

        return x && y;
    }
}