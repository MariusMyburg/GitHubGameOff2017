#pragma once
#include "AnimatedSprite.h"

class PhysicsBlock
{
public:
    PhysicsBlock(sf::RenderWindow* renderWindow, std::string filename, b2World* b2world, b2BodyType bodyType, double posx, double posy);
    ~PhysicsBlock();

    sf::Vector2f GetPosition();
    void SetPosition(sf::Vector2f position);
    void SetPhysicsPosition(float x, float y);

    void Update();
    void Draw(sf::RenderStates states) const;


private:
    AnimatedSprite* mptrSprite;

    sf::RenderWindow* mptrRenderWindow;

    // Physics
    b2Body* mptrb2Body;
    b2BodyType mb2BodyType;
    b2Shape* mptrb2Shape;
    b2Fixture* mptrFixture;
};

