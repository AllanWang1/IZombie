#include "PlayState.h"

#include "definitions.h"
#include <random>
#include <iostream>
#include "GameOverState.h"

// Class that represents the playing state of the game.
namespace izombie
{
    // Modifies: this
    PlayState::PlayState(GameDataRef data) : _data(data)
    {

    }

    // Modifies: _data, zombie, spike, collision
    // Effects: initializes the playing state, assigns the different textures for the player frames
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
        hp = new HealthBar(_data);
        collision = new Collision();
    }

    // Modifies: _data
    // Effects: handles inputs. If space pressed then call zombie->Tap()
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

    // Modifies: this, zombie, spike
    // Effects: uses a clock to randomly generate the spikes, and animates the zombie. When player is
    //          not invincible, check for collisions.
    void PlayState::Update(float dt)
    {
        if (!_dead)
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

            // check the collisions if player isn't invincible, if collided, stop all movements
            if (!zombie->GetInvincibilityStatus())
            {
                std::vector<sf::Sprite> spikeweedSprites = spike->GetSpikeweedSprites();
                for (const auto & spikeweedSprite : spikeweedSprites)
                {
                    if (collision->Collided(zombie->GetSprite(), spikeweedSprite))
                    {
                        zombie->GetHurt();
                        hp->Update(zombie->GetHealth());
                        if (zombie->GetHealth() <= 0)
                        {
                            _dead = true;
                            _data->machine.AddState(StateRef(new GameOverState(_data)),
                                                    true);
                        }
                    }
                }
            }
        }
    }

    // Modifies: this
    // Effects: calls draw on zombie, spike, and display background on window.
    void PlayState::Draw(float dt)
    {
        _data -> window.clear();
        _data -> window.draw(_background);
        zombie -> Draw();
        spike -> DrawSpikeweeds();
        hp -> Draw();
        _data->window.display();
    }

}
