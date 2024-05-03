#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "InputManager.h"
#include "StateMachine.h"

namespace izombie
{
    // GameData type contains
    struct GameData
    {
        StateMachine machine;
        sf::RenderWindow window;
        AssetManager assets;
        InputManager input;
    };
    typedef std::shared_ptr<GameData> GameDataRef;


    class Game
    {
    public:
        Game (int width, int height, std::string title);
    private:
        const float dt = 1.0f/60.0f;
        // clock to keep track of game time in all ways
        sf::Clock _clock;

        // this is game data
        GameDataRef _data = std::make_shared<GameData>();

        void Run();
    };
}
