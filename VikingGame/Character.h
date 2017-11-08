#pragma once
#include "AnimatedSprite.h"
#include <map>

class Character
{
public:
    Character(sf::RenderWindow* renderWindow, b2World* ptrBox2DWorld);
    ~Character();

    AnimatedSprite* AddAnimatedSprite(std::string ID, float FPS);
    AnimatedSprite* GetAnimatedSpriteForID(std::string ID);

    void SetPosition(float x, float y);

    void SetCurrentAnimation(std::string animationID);
    std::string GetCurrentAnimation();

    void Jump();
    bool IsInAir();

    virtual void HandleInput() = 0;
    virtual void Update(float dt);
    void Draw(sf::RenderStates states);


    void RegisterForPhysics(b2World* ptrWorld, b2BodyType type, float mass, double posx, double posy);

    void SetPhysicsPosition(float x, float y);
    b2Vec2 GetPhysicsPosition();

    b2World* GetBox2DWorld();
    void DisablePhysics();
    void EnablePhysics();

    std::vector<std::string> AnimationIDs() const;

private:    
    sf::RenderWindow* mptrRenderWindow;
    std::map<std::string, AnimatedSprite*> mmapAnimatedSprites;
    std::string mstrCurrentAnimationID;

    /* Box2D Physics */
    b2World* mptrBox2DWorld;
    b2Body* mptrb2Body;
    b2ChainShape* mptrb2ChainShape;
    b2Fixture* mptrFixture;
};

