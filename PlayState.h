#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Spikeweed.h"
#include "Player.h"
#include "Collision.h"
#include "HealthBar.h"
namespace izombie
{
    class PlayState : public State
    {
    public:
        PlayState(GameDataRef data);

        void Init();

        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataRef _data;

        sf::Sprite _background;

        Spikeweed *spike{};
        Player *zombie{};
        HealthBar *hp{};
        Collision *collision{};
        sf::Clock _clock;

        bool _dead{};
    };
}

