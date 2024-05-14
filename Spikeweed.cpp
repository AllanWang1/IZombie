#include "Spikeweed.h"

namespace izombie
{
    // Modifies: this
    Spikeweed::Spikeweed(GameDataRef data): _data(data)
    {

    }

    // Modifies: _data, spikeweeds
    // Effects: sets initial position of every spikeweed, and pushes newly spawns spikeweeds to spikeweeds
    void Spikeweed::Spawn()
    {
        sf::Sprite spikeweed(_data->assets.GetTexture("Spikeweed"));
        spikeweed.setPosition(_data->window.getSize().x,
                           _data->window.getSize().y - (spikeweed.getGlobalBounds().height + 50));
        spikeweeds.push_back(spikeweed);
    }

    // Modifies: this
    // Effects: Moves all spikeweeds in the vector at the same speed
    void Spikeweed::Move(float dt)
    {
        for(int i = 0; i < spikeweeds.size(); i++)
        {
            if (spikeweeds.at(i).getPosition().x < 0 - spikeweeds.at(i).getGlobalBounds().width)
            {
                spikeweeds.erase(spikeweeds.begin() + i);
            } else
            {
                // frame independent, higher framerate -> less moved per second
                float movement = SPIKEWEED_MOVEMENT_SPEED * dt + _totalTime.getElapsedTime().asSeconds() / 5;

                spikeweeds.at(i).move(-movement, 0);
            }
        }
    }

    // Modifies: this
    // Effects: draws every spikeweed in the window.
    void Spikeweed::DrawSpikeweeds()
    {
        for (int i = 0; i < spikeweeds.size(); i++)
        {
            _data->window.draw(spikeweeds.at(i));
        }
    }

    std::vector<sf::Sprite> Spikeweed::GetSpikeweedSprites()
    {
        return spikeweeds;
    }
}