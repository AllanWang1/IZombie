#include "Game.h"
#include "MainMenuState.h"

namespace izombie
{
    // Modifies: this
    // Effects: Creates and assigns a window to _data given width, height, and title; then run the Game
    Game::Game(int width, int height, std::string title)
    {
        _data -> window.create(sf::VideoMode(width, height), title,
                               sf::Style::Close | sf::Style::Titlebar);
        // add the first state to states machine stack
        _data -> machine.AddState(StateRef(new MainMenuState(this->_data)));
        this -> Run();
    }

    // Modifies: this
    // Effects: runs the game loop. Updates game logic and draws on current state
    void Game::Run()
    {
        float newTime;
        float frameTime;
        float interpolation;

        float currentTime = this -> _clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while (this -> _data -> window.isOpen())
        {
            this -> _data -> machine.ProcessStateChanges();

            newTime = this -> _clock.getElapsedTime().asSeconds();
            frameTime = newTime - currentTime;

            if (frameTime > 0.25f)
            {
                frameTime = 0.25f;
            }

            currentTime = newTime;
            accumulator += frameTime;

            while (accumulator >= dt)
            {
                this -> _data -> machine.GetActiveState() -> HandleInput();
                this -> _data -> machine.GetActiveState() -> Update(dt);

                accumulator -= dt;
            }

            interpolation = accumulator / dt;
            this -> _data -> machine.GetActiveState() -> Draw(interpolation);
        }
    }
}