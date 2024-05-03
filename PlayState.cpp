#include "PlayState.h"

#include <sstream>
#include "definitions.h"
#include <random>
#include <iostream>

namespace izombie
{
    PlayState::PlayState(GameDataRef data) : _data(data)
    {

    }

    void PlayState::Init()
    {
        _data -> assets.LoadTexture("Game Background",
                                    GAME_BACKGROUND_FILEPATH);
        _data -> assets.LoadTexture("Spikeweed",
                                    SPIKEWEED_FILEPATH);
        _data -> assets.LoadTexture("Zombie1",
                                    ZOMBIE_1_FILEPATH);

        _background.setTexture(this -> _data -> assets.GetTexture("Game Background"));

        spike = new Spikeweed(_data);
        zombie = new Player(_data);
    }

    void PlayState::HandleInput()
    {
        sf::Event event;
        while (_data -> window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
                _data -> window.close();
        }
    }

    void PlayState::Update(float dt)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(15,55);
        float random_time = ((float) dis(gen)) / 10;
        spike->Move(dt);
        if (_clock.getElapsedTime().asSeconds() > random_time)
        {
            spike->Spawn();
            _clock.restart();
        }
    }

    void PlayState::Draw(float dt)
    {
        _data->window.clear();
        _data->window.draw(_background);
        zombie->Draw();
        spike->DrawSpikeweeds();
        _data->window.display();
    }

}
