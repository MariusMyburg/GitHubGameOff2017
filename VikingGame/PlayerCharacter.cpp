#include "stdafx.h"
#include "PlayerCharacter.h"
#include "SFMLDebugDraw.h"
#include "Game.h"


PlayerCharacter::PlayerCharacter(sf::RenderWindow* renderWindow, b2World* ptrBox2DWorld, double posx, double posy): Character(renderWindow, ptrBox2DWorld)
{
    Game::Instance()->setPlayerCharacter(this);

    /* IDLE */
    AnimatedSprite* idleAnimatedSprite = AddAnimatedSprite("Idle", 0.5f);    
    idleAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/1_IDLE_000_colorer.png");
    idleAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/1_IDLE_001_colorer.png");
    idleAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/1_IDLE_002_colorer.png");
    idleAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/1_IDLE_003_colorer.png");
    idleAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/1_IDLE_004_colorer.png");



    /* WALK */
    AnimatedSprite* walkAnimatedSprite = AddAnimatedSprite("Walk", 5);
    /*walkAnimatedSprite->AddFrame("../Images/Viking/Small/2_WALK_000_result.png");
    walkAnimatedSprite->AddFrame("../Images/Viking/Small/2_WALK_001_result.png");
    walkAnimatedSprite->AddFrame("../Images/Viking/Small/2_WALK_002_result.png");
    walkAnimatedSprite->AddFrame("../Images/Viking/Small/2_WALK_003_result.png");
    walkAnimatedSprite->AddFrame("../Images/Viking/Small/2_WALK_004_result.png");*/
    walkAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/2_WALK_000_colorer.png");
    walkAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/2_WALK_001_colorer.png");
    walkAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/2_WALK_002_colorer.png");
    walkAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/2_WALK_003_colorer.png");
    walkAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/2_WALK_004_colorer.png");

    /* JUMP */
    AnimatedSprite* jumpAnimatedSprite = AddAnimatedSprite("Jump", 1);
    //jumpAnimatedSprite->AddFrame("../Images/Viking/Small/4_JUMP_000_result.png");
    /*jumpAnimatedSprite->AddFrame("../Images/Viking/Small/4_JUMP_001_result.png");
    jumpAnimatedSprite->AddFrame("../Images/Viking/Small/4_JUMP_002_result.png");
    jumpAnimatedSprite->AddFrame("../Images/Viking/Small/4_JUMP_003_result.png");
    jumpAnimatedSprite->AddFrame("../Images/Viking/Small/4_JUMP_004_result.png");*/
    jumpAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/4_JUMP_000_colorer.png");
    jumpAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/4_JUMP_001_colorer.png");
    jumpAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/4_JUMP_002_colorer.png");
    jumpAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/4_JUMP_003_colorer.png");
    jumpAnimatedSprite->AddFrame("C:/Users/Marius/Desktop/GameArt_Processed/craftpix-339912-2d-fantasy-wizards-sprite-sheets/PNG/1_WIZARD/resized/4_JUMP_004_colorer.png");

    RegisterForPhysics(GetBox2DWorld(), b2BodyType::b2_dynamicBody, 1, posx, posy);

    GetBox2DWorld()->SetContactListener(mptrContactListener);

    EnablePhysics();
}


PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::Update(float dt)
{
    Character::Update(dt);
    
    if (mbWalkingForwards && !IsInAir())
    {
        SetCurrentAnimation("Walk");
    }else if (!mbWalkingForwards && !mbWalkingBackwards && !IsInAir())
    {
        SetCurrentAnimation("Idle");
    }else if (IsInAir())
    {
        SetCurrentAnimation("Jump");
    }
}

void PlayerCharacter::HandleInput()
{
    mbWalkingForwards = false;
    mbWalkingBackwards = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        Jump();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        mbWalkingForwards = false;
        mbWalkingBackwards = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        mbWalkingForwards = true;
        mbWalkingBackwards = false;

        getPhysicsBody()->ApplyForceToCenter(b2Vec2(0.005f, 0), true);
    }
}
