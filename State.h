//
// Switching between different states of the game
//
#pragma once

class State
{
public:
    virtual void Init() = 0;
    virtual void HandleInput() = 0;
    virtual void Update(float frequency) = 0;
    virtual void Draw(float frequency) = 0;

    virtual void Pause() {}
    virtual void Resume() {}
};