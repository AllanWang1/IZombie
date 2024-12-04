#include "GameOverState.h"
#include "PlayState.h"
#include <sstream>
#include "definitions.h"


namespace izombie
{
    GameOverState::GameOverState(GameDataRef data) : _data(data)
    {

    }

    void GameOverState::Init()
    {
        _data -> assets.LoadTexture("Game Over Background",
                                    GAME_OVER_BACKGROUND_FILEPATH);
        _data -> assets.LoadTexture("Restart Button",
                                    RESTART_BUTTON_FILEPATH);
        _background.setTexture(this -> _data -> assets.GetTexture("Game Over Background"));
        _restartButton.setTexture(this -> _data -> assets.GetTexture("Restart Button"));
        _restartButton.setPosition(SCREEN_WIDTH/4,
                                   SCREEN_HEIGHT - _restartButton.getGlobalBounds().height);
        _restartButton.setScale(0.3f, 0.3f);
    }

    void GameOverState::HandleInput()
    {
        sf::Event event;
        while (_data -> window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
                _data -> window.close();
            if (_data->input.IsSpriteClicked(_restartButton,
                                             sf::Mouse::Left,
                                             _data->window))
            {
                _data->machine.AddState(StateRef(new PlayState(_data)), true);
            }
        }
    }

    void GameOverState::Update(float dt)
    {

    }

    void GameOverState::Draw(float dt)
    {
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.draw(_restartButton);
        _data->window.display();
    }

}
