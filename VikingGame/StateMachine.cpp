#include "stdafx.h"
#include "StateMachine.h"

void StateMachine::AddState(State* state, bool isReplacing)
{
    if (isReplacing)
    {
        mStates.pop();
    }

    mStates.push(state);
    mStates.top()->Initialize();    
}

void StateMachine::RemoveTopState()
{
    if (!mStates.empty())
    {
        mStates.pop();

        if (!mStates.empty())
        {
            mStates.top()->Resume();
        }
    }
}

State* StateMachine::GetActiveState()
{
    return mStates.top();
}
