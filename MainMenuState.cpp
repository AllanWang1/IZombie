#include "MainMenuState.h"

#include <sstream>
#include "definitions.h"
#include "PlayState.h"
#include <iostream>

namespace izombie
{
    MainMenuState::MainMenuState(GameDataRef data) : _data(data)
    {

    }

    void MainMenuState::Init()
    {
        _data -> assets.LoadTexture("Main Menu Background",
                                    MAIN_MENU_BACKGROUND_FILEPATH);
        _data -> assets.LoadTexture("Play Button",
                                    PLAY_BUTTON_FILEPATH);

        _background.setTexture(this -> _data -> assets.GetTexture("Main Menu Background"));
        _playButton.setTexture(this -> _data -> assets.GetTexture("Play Button"));

        _playButton.setPosition((SCREEN_WIDTH / 2) - _playButton.getGlobalBounds().width/2,
                                (SCREEN_HEIGHT) - _playButton.getGlobalBounds().height);
    }

    void MainMenuState::HandleInput()
    {
        sf::Event event;
        while (_data -> window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
                _data -> window.close();

            if (_data->input.IsSpriteClicked(_playButton,
                                             sf::Mouse::Left,
                                             _data->window))
            {
                _data->machine.AddState(StateRef(new PlayState(_data)), true);
                sf::SoundBuffer buffer;
                buffer.loadFromFile(PLAY_BUTTON_SOUND_FILEPATH);
                sf::Sound sound;
                sound.setBuffer(buffer);
                sound.play();
            }
        }
    }

    void MainMenuState::Update(float dt)
    {

    }

    void MainMenuState::Draw(float dt)
    {
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.draw(_playButton);
        _data->window.display();
    }

}