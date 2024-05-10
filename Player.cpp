#include "Player.h"

namespace izombie
{
    Player::Player(GameDataRef data): _data(data)
    {
        _animationIterator = 0;
        _zombieState = ZOMBIE_STILL_STATE;
        _zombieFrames.push_back(_data->assets.GetTexture("Zombie1"));
        _zombieFrames.push_back(_data->assets.GetTexture("Zombie2"));
        _zombieFrames.push_back(_data->assets.GetTexture("Zombie3"));
        _zombieFrames.push_back(_data->assets.GetTexture("Zombie4"));
        _zombieFrames.push_back(_data->assets.GetTexture("Zombie5"));
        _zombie.setTexture((_zombieFrames.at(_animationIterator)));

        _basePosition = sf::Vector2f(_zombie.getGlobalBounds().width/2,
                                     (float) _data->window.getSize().y - _zombie.getGlobalBounds().height - 50);
        _zombie.setPosition(_basePosition);

        _hitbox.setSize(sf::Vector2f (_zombie.getGlobalBounds().width,
                                      _zombie.getGlobalBounds().height));
        _hitbox.setPosition(_basePosition);
        _hitbox.setOutlineColor(sf::Color::Blue);
        _hitbox.setOutlineThickness(5.f);
        _hitbox.setFillColor(sf::Color::Transparent);
    }

    void Player::Draw()
    {
        _data->window.draw(_zombie);
        _data->window.draw(_hitbox);
    }

    void Player::Animate()
    {
        if (_clock.getElapsedTime().asSeconds() > ZOMBIE_ANIMATION_DURATION/ (float) _zombieFrames.size())
        {
            if (_animationIterator < _zombieFrames.size() - 1)
            {
                _animationIterator++;
            }
            else
            {
                _animationIterator = 0;
            }
            _zombie.setTexture(_zombieFrames.at(_animationIterator));
            _clock.restart();
        }
    }

    void Player::Update(float dt)
    {
        if (_zombieState == ZOMBIE_JUMP_STATE)
        {
            _zombie.move(0, -GRAVITY * dt);
        }
        else if (_zombieState == ZOMBIE_FALL_STATE)
        {
            _zombie.move(0, GRAVITY * dt);
        }
        else if (_zombieState == ZOMBIE_STILL_STATE)
        {
            _zombie.setPosition(_basePosition);
        }


        if (_hasBeenTapped)
        {
            if (_jumpClock.getElapsedTime().asSeconds() > JUMP_DURATION)
            {
                _zombieState = ZOMBIE_FALL_STATE;
            }
            if (_fallClock.getElapsedTime().asSeconds() > FALL_DURATION)
            {
                _zombieState = ZOMBIE_STILL_STATE;
            }
        }
        _hitbox.setPosition(_zombie.getPosition());
    }

    void Player::Tap()
    {
        _hasBeenTapped = true;
        if (_zombieState == ZOMBIE_STILL_STATE && _zombie.getPosition() == _basePosition)
        {
            _zombieState = ZOMBIE_JUMP_STATE;
            _jumpClock.restart();
            _fallClock.restart();
        }
    }

    const sf::Sprite &Player::GetSprite() const
    {
        return _zombie;
    }
}