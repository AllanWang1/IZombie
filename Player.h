#pragma once

#include <SFML/Graphics.hpp>

#include "definitions.h"
#include "Game.h"

namespace izombie
{
    class Player
    {
    public:
        Player(GameDataRef data);

        void Draw();

        void Update(float dt);

        void Tap();

    private:
        GameDataRef _data;
        sf::Sprite _zombie;
    };
}
