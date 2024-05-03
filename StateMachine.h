#pragma once

#include <memory>
#include <stack>

#include "State.h"

typedef std::unique_ptr<State> StateRef;

class StateMachine
{
public:
    StateMachine() {}
    ~StateMachine() {}

    void AddState(StateRef newState, bool isReplacing = true);
    void RemoveState();

    void ProcessStateChanges();

    StateRef &GetActiveState();

private:
    // A stack to store the upcoming states
    std::stack<StateRef> states;
    StateRef newState;
    bool isRemoving;
    bool isAdding;
    bool isReplacing;
};
