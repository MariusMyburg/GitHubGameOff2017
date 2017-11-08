#pragma once
#include "State.h"
#include <list>
#include "Box2D.h"

class PhysicsTestState: public State
{
public:
    PhysicsTestState();
    ~PhysicsTestState();

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

    b2World* mptrBox2DWorld;
    std::list<b2Body*> bodies;


    b2Body* createBox(b2World& world,int pos_x,int pos_y, int size_x,int size_y,b2BodyType type = b2_dynamicBody);
};

