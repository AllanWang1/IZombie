#include "StateMachine.h"

// Modifies: this
// Effects: sets isAdding to true; takes in newState parameter and sets it as the new State with std::move.
void StateMachine::AddState(StateRef newState, bool isReplacing)
{
    this->isAdding = true;
    this->isReplacing = isReplacing;
    this->newState = std::move(newState);
}

// Modifies: this
// Effects: sets isRemoving to true
void StateMachine::RemoveState()
{
    this->isRemoving = true;
}

// Modifies: this
// Effects: check if state needs to be changed, process them if needed.
// - If there are states and isRemoving, then pop the top of the states stack
//      - Further, if the stack is not empty, resume the next state
//      - Then finish the removal by setting isRemoving = false
// - If isAdding:
//      - First, deal with the top state that was running. Pop it if we replace the top state, pause if we aren't
//      - Push the new state to top of stack and initialize it. Set isAdding = false
void StateMachine::ProcessStateChanges()
{
    // If there is a state and it is being removed
    if (this->isRemoving && !this->states.empty())
    {
        this -> states.pop();
        if (!this -> states.empty())
            this -> states.top()->Resume(); // Resume the next state

        this -> isRemoving = false;
    }

    if(this -> isAdding)
    {
        if (!this->states.empty())
        {
            if (this -> isReplacing)
            {
                this -> states.pop();
            }
            else
            {
                this -> states.top() -> Pause();
            }
        }

        this -> states.push(std::move(this -> newState));
        this -> states.top() -> Init();
        this -> isAdding = false;
    }
}

// Effects: return the state on top of the stack (the active state)
StateRef &StateMachine::GetActiveState()
{
    return this -> states.top();
}

