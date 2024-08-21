cmake_minimum_required(VERSION 3.14)
project(IZombie)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        definitions.h
        State.h
        StateMachine.cpp
        StateMachine.h
        AssetManager.cpp
        AssetManager.h
        InputManager.cpp
        InputManager.h
        Game.cpp
        Game.h
        MainMenuState.cpp
        MainMenuState.h
        PlayState.cpp
        PlayState.h
        GameOverState.cpp
        GameOverState.h
        Spikeweed.cpp
        Spikeweed.h
        Player.cpp
        Player.h
        Collision.cpp
        Collision.h
        HealthBar.cpp
        HealthBar.h
)
add_executable(IZombie ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(IZombie sfml-system sfml-window sfml-graphics sfml-audio sfml-network)