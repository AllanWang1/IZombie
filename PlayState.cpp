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
        _data -> assets.LoadTexture("Zombie2",
                                    ZOMBIE_2_FILEPATH);
        _data -> assets.LoadTexture("Zombie3",
                                    ZOMBIE_3_FILEPATH);
        _data -> assets.LoadTexture("Zombie4",
                                    ZOMBIE_4_FILEPATH);
        _data -> assets.LoadTexture("Zombie5",
                                    ZOMBIE_5_FILEPATH);

        _background.setTexture(this -> _data -> assets.GetTexture("Game Background"));
        zombie = new Player(_data);
        spike = new Spikeweed(_data);
        collision = new Collision();
    }

    void PlayState::HandleInput()
    {
        sf::Event event;
        while (_data -> window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
                _data -> window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                zombie->Tap();
            }
        }
    }

    void PlayState::Update(float dt)
    {
        if (!dead)
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
            zombie->Animate();
            zombie->Update(dt);

            // check the collisions, if collided, stop all movements
            std::vector<sf::Sprite> spikeweedSprites = spike->GetSpikeweedSprites();
            for (const auto & spikeweedSprite : spikeweedSprites)
            {
                if (collision->Collided(zombie->GetSprite(), spikeweedSprite))
                {
                    dead = true;
                }
            }
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
