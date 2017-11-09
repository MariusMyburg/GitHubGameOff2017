#pragma once
#include "State.h"
#include <memory>
#include <stack>

//typedef std::unique_ptr<State> StateRef;

class StateMachine
{
public:
    StateMachine() { };
    ~StateMachine();

    void AddState(State* state, bool isReplacing);
    void RemoveTopState();

    State* GetActiveState();

private:
    std::stack<State*> mStates;
};