#pragma once
#include "State.h"

class DumDumState: public State
{
public:
    DumDumState();
    ~DumDumState();

    // Inherited via State
    virtual void Initialize() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow & target) override;
    virtual void Pause() override;
    virtual void Resume() override;
    virtual void HandleInput() override;


private:
    sf::Clock mClock;
    sf::Time mRunTime;
    sf::Font mBigFont;
    sf::Text mBigText;
};

