#include <SFML/Graphics.hpp>

#include <iostream>
#include "definitions.h"
#include "Game.h"
#include <vector>

namespace izombie {
    class HealthBar
    {
    public:
        HealthBar(GameDataRef data);

        void Draw();

        void Update(int hp);

    private:
        GameDataRef _data;
        sf::Sprite _fullHeart;
        sf::Sprite _emptyHeart;
        std::vector<sf::Sprite> _hearts;
        int _health;
        sf::Vector2f _basePosition;
    };
}
