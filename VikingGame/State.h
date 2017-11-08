#pragma once
#include "SFML/Graphics.hpp"

class State
{
public:
    State() { };
    ~State() { };

    virtual void Initialize() = 0;
    virtual void Update(float dt) = 0;
    virtual void Draw(sf::RenderWindow& target) = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual void HandleInput() = 0;


private:
    sf::View* mptrCamera;
};