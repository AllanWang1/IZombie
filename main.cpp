#include <SFML/Graphics.hpp>
#include <iostream>
#include "definitions.h"
#include "Game.h"
#include "MainMenuState.h"




int main()
{
    izombie::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "IZombie");

    return EXIT_SUCCESS;
}
