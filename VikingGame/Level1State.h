#pragma once
#include "State.h"
#include "ParallaxInfiniteScroller.h"
#include "PlayerCharacter.h"
#include "PhysicsBlock.h"
#include "OverlapCallbackRectangleManager.h"

class Level1State : public State
{
public:
    Level1State();
    ~Level1State();

    // Inherited via State
    virtual void Initialize() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow & target) override;
    virtual void Pause() override;
    virtual void Resume() override;
    virtual void HandleInput() override;


private:
    ParallaxInfiniteScroller* mptrBackground;
    ParallaxInfiniteScroller* mptrMountains_fg;
    ParallaxInfiniteScroller* mptrGround;
    ParallaxInfiniteScroller* mptrGrass;
    ParallaxInfiniteScroller* mptrCactus;
    ParallaxInfiniteScroller* mptrShip;

    std::vector<PhysicsBlock*> mvecBlocks;

    PlayerCharacter* mptrPlayer;
    b2World* mptrBox2DWorld;

    //OverlapCallbackRectangleManager* mptrOverlapCallbackRectangleManager;

    OverlapCallbackRectangle* mptrRect1;
    OverlapCallbackRectangle* mptrRect2;
};

