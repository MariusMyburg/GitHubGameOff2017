#include "stdafx.h"
#include "PlayerCharacter.h"
#include "SFMLDebugDraw.h"


PlayerCharacter::PlayerCharacter(sf::RenderWindow* renderWindow, b2World* ptrBox2DWorld, double posx, double posy): Character(renderWindow, ptrBox2DWorld)
{
    /* IDLE */
    AnimatedSprite* idleAnimatedSprite = AddAnimatedSprite("Idle", 1);
    idleAnimatedSprite->AddFrame("../Images/Viking/Small/1_IDLE_000_result.png");
    /*idleAnimatedSprite->AddFrame("../Images/Viking/Small/1_IDLE_001_result.png");
    idleAnimatedSprite->AddFrame("../Images/Viking/Small/1_IDLE_002_result.png");
    idleAnimatedSprite->AddFrame("../Images/Viking/Small/1_IDLE_003_result.png");
    idleAnimatedSprite->AddFrame("../Images/Viking/Small/1_IDLE_004_result.png");*/

    /* WALK */
    AnimatedSprite* walkAnimatedSprite = AddAnimatedSprite("Walk", 5);
    walkAnimatedSprite->AddFrame("../Images/Viking/Small/2_WALK_000_result.png");
    /*walkAnimatedSprite->AddFrame("../Images/Viking/Small/2_WALK_001_result.png");
    walkAnimatedSprite->AddFrame("../Images/Viking/Small/2_WALK_002_result.png");
    walkAnimatedSprite->AddFrame("../Images/Viking/Small/2_WALK_003_result.png");
    walkAnimatedSprite->AddFrame("../Images/Viking/Small/2_WALK_004_result.png");*/

    /* JUMP */
    AnimatedSprite* jumpAnimatedSprite = AddAnimatedSprite("Jump", 1);
    jumpAnimatedSprite->AddFrame("../Images/Viking/Small/4_JUMP_000_result.png");
    /*jumpAnimatedSprite->AddFrame("../Images/Viking/Small/4_JUMP_001_result.png");
    jumpAnimatedSprite->AddFrame("../Images/Viking/Small/4_JUMP_002_result.png");
    jumpAnimatedSprite->AddFrame("../Images/Viking/Small/4_JUMP_003_result.png");
    jumpAnimatedSprite->AddFrame("../Images/Viking/Small/4_JUMP_004_result.png");*/

    
    
    RegisterForPhysics(GetBox2DWorld(), b2BodyType::b2_dynamicBody, 1, posx, posy);

    EnablePhysics();
}


PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::Update(float dt)
{
    Character::Update(dt);
    
    if (mbWalking && !IsInAir())
    {
        SetCurrentAnimation("Walk");
        SetPhysicsPosition(GetPhysicsPosition().x + 0.01f, GetPhysicsPosition().y);
    }else if (!mbWalking && !IsInAir())
    {
        SetCurrentAnimation("Idle");
        //SetPhysicsPosition(GetPhysicsPosition().x, GetPhysicsPosition().y);
    }else if (IsInAir())
    {
        SetCurrentAnimation("Jump");
        //SetPhysicsPosition(GetPhysicsPosition().x, GetPhysicsPosition().y);
    }
}

void PlayerCharacter::HandleInput()
{
    mbWalking = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        Jump();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        mbWalking = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        mbWalking = true;
    }
}
