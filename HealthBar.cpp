//
// Created by Allan Wang on 2024-08-21.
//

#include "HealthBar.h"

namespace izombie {

    HealthBar::HealthBar(GameDataRef data): _data(data)
    {
        _data -> assets.LoadTexture("FullHeart",
                                    FULL_HEART_FILEPATH);
        _data -> assets.LoadTexture("EmptyHeart",
                                    EMPTY_HEART_FILEPATH);
        _fullHeart.setTexture(_data -> assets.GetTexture("FullHeart"));
        _emptyHeart.setTexture(_data -> assets.GetTexture("EmptyHeart"));
        _fullHeart.setScale(0.5f, 0.5f);
        _emptyHeart.setScale(0.5f, 0.5f);

        for (int i = 0; i < INITIAL_HEALTH; i++)
        {
            _hearts.push_back(_fullHeart);
        }
        _health = INITIAL_HEALTH;

        _basePosition = sf::Vector2f(_fullHeart.getGlobalBounds().width/2,
                                     _fullHeart.getGlobalBounds().height - 50);

    }

    void HealthBar::Draw()
    {
        for (int i = 0; i < _hearts.size(); i++)
        {
            _hearts[i].setPosition(_basePosition.x + 1.5 * i * _fullHeart.getGlobalBounds().width,
                                   _basePosition.y);
            _data -> window.draw(_hearts[i]);
        }
    }

    void HealthBar::Update(int hp)
    {
        this -> _health = hp;
        _hearts.clear();
        for (int i = 0; i < _health; i++)
        {
            _hearts.push_back(_fullHeart);
        }
        for (int i = 0; i < INITIAL_HEALTH - _health; i++)
        {
            _hearts.push_back(_emptyHeart);
        }
    }

}
