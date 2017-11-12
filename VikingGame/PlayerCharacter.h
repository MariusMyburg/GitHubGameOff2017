#pragma once
#include "Character.h"

class PlayerCharacter: public Character
{
public:
    PlayerCharacter(sf::RenderWindow* renderWindow, b2World* ptrBox2DWorld, double posx, double posy);
    ~PlayerCharacter();

    // Inherited via Character
    virtual void HandleInput() override;
    void Update(float dt) override;

private:
    bool mbWalkingForwards;
    bool mbWalkingBackwards;
};

