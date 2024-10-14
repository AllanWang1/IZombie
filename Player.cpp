#include "Player.h"

namespace izombie
{
    // Modifies: this
    // Effects: initializes the player, sets images for each frame, sets position and hitbox of the player.
    //          Also initializes _animationIterator to 0
    Player::Player(GameDataRef data): _data(data)
    {
        _animationIterator = 0;
        _zombieState = ZOMBIE_STILL_STATE;
        _invincible = false;
        _health = INITIAL_HEALTH;
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
        _hitbox.setOutlineColor(sf::Color::Yellow);
        _hitbox.setOutlineThickness(5.f);
        _hitbox.setFillColor(sf::Color::Transparent);
    }

    // Modifies: _data
    // Effects: draws the player on screen
    void Player::Draw()
    {
        _data->window.draw(_zombie);
        if (_invincible)
            _data->window.draw(_hitbox);
    }

    // Modifies: this
    // Effects: sets the texture of the player to the next image in _zombieFrames if a certain amount of time has
    //          passed. Set the texture to the first image _zombieFrames if currently on the last image.
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

    // Requires: dt > 0
    // Modifies: this
    // Effects: move the player sprite according to the current state of the player. Switch the state of
    //          the player according to _jumpClock and _fallClock. Sets the hitbox's position to the player's.
    //          Check if invincibility has passed, turn off invincibility.
    void Player::Update(float dt)
    {
        // std::cout << _zombieState << std::endl;
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
            // Forcefully set the player's position down to _basePosition
            _zombie.setPosition(_basePosition);
        }

        // _jumpClock starts at initialization, and once we enter the game, _jumpClock is already past JUMP_DURATION.
        // Must also apply condition where _zombieState is what we are expecting it to be when we check.
        if (_jumpClock.getElapsedTime().asSeconds() > JUMP_DURATION && _zombieState == ZOMBIE_JUMP_STATE)
        {
            _zombieState = ZOMBIE_FALL_STATE;
        }
        if (_fallClock.getElapsedTime().asSeconds() > FALL_DURATION && _zombieState == ZOMBIE_FALL_STATE)
        {
            _zombieState = ZOMBIE_STILL_STATE;
        }

        if (_invincibilityClock.getElapsedTime().asSeconds() > INVINCIBILITY_DURATION)
            _invincible = false;
        _hitbox.setPosition(_zombie.getPosition());
    }

    // Modifies: this
    // Effects: if player state is still, then set the player state to jumping, and restart both _jumpClock and
    //          _fallClock in order to let the player sprite fall down at the right time.
    void Player::Tap()
    {
        if (_zombieState == ZOMBIE_STILL_STATE && _zombie.getPosition() == _basePosition)
        {
            _zombieState = ZOMBIE_JUMP_STATE;
            _jumpClock.restart();
            _fallClock.restart();
        }
    }

    // Modifies: this
    // Effects: shifts the pixels of the player sprite red, then set it back after _hurtClock reaches HURT_DURATION.
    void Player::GetHurt()
    {
        _health --;
        _invincible = true;
        _invincibilityClock.restart();
        unsigned int textureWidth = _zombieFrames.at(_animationIterator).getSize().x;
        unsigned int textureHeight = _zombieFrames.at(_animationIterator).getSize().y;
        sf::Uint8* pixels = new sf::Uint8[textureWidth * textureHeight * 4];
        sf::Image image = _zombieFrames.at(_animationIterator).copyToImage();
        std::memcpy(pixels, image.getPixelsPtr(), textureWidth * textureHeight * 4);

        // turning the frame more red
        for (unsigned int x = 0; x < textureWidth; x++) {
            for (unsigned int y = 0; y < textureHeight; y++) {
                unsigned int index = (x * textureHeight + y) * 4;
                if (pixels[index] + 50 >= 255)
                {
                    pixels[index] = 255;
                }
                else
                {
                    pixels[index] += 50;
                }
            }
        }
        _zombieFrames.at(_animationIterator).update(pixels);
        _zombie.setTexture(_zombieFrames.at(_animationIterator));
        delete[] pixels;
    }

    const sf::Sprite &Player::GetSprite() const
    {
        return _zombie;
    }

    bool Player::GetInvincibilityStatus() const
    {
        return _invincible;
    }

    int Player::GetHealth() const
    {
        return _health;
    }
}