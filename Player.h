#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
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

        const sf::Sprite &GetSprite() const;

        void GetHurt();

        bool GetInvincibilityStatus() const;

        int GetHealth() const;
    private:
        GameDataRef _data;
        sf::Sprite _zombie;
        sf::RectangleShape _hitbox;

        std::vector<sf::Texture> _zombieFrames;
        unsigned int _animationIterator;

        sf::Clock _clock;

        sf::Clock _jumpClock;
        sf::Clock _fallClock;

        int _zombieState;

        bool _hasBeenTapped;
        sf::Vector2f _basePosition;

        bool _invincible;
        sf::Clock _invincibilityClock;

        int _health;
    };
}
