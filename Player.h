#pragma once

#include <SFML/Graphics.hpp>

#include "definitions.h"
#include "Game.h"
#include <vector>
namespace izombie
{
    class Player
    {
    public:
        Player(GameDataRef data);

        void Draw();

        void Animate();

        void Update(float dt);

        void Tap();

    private:
        GameDataRef _data;
        sf::Sprite _zombie;

        std::vector<sf::Texture> _zombieFrames;
        unsigned int _animationIterator;

        sf::Clock _clock;

        sf::Clock _jumpClock;
        sf::Clock _fallClock;

        int _zombieState;
    };
}
