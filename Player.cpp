#include "Player.h"

namespace izombie
{
    Player::Player(GameDataRef data): _data(data)
    {
        _zombie.setTexture(_data->assets.GetTexture("Zombie1"));
        _zombie.setPosition(_zombie.getGlobalBounds().width/2,
                            _data->window.getSize().y - _zombie.getGlobalBounds().height - 50);
    }

    void Player::Draw()
    {
        _data->window.draw(_zombie);
    }
}