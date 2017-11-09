#include "stdafx.h"
#include "Level1State.h"
#include "ParallaxInfiniteScroller.h"
#include "PlayerCharacter.h"
#include "PhysicsBlock.h"
#include "AssetManager.h"
#include "Game.h"
#include "SfmlDebugDraw.h"
#include "OverlapCallbackRectangle.h"



void overlapHandler(OverlapCallbackRectangle* ptrSelf, OverlapCallbackRectangle* ptrOther)
{
    
}


Level1State::Level1State()
{
}


Level1State::~Level1State()
{
    delete mptrBox2DWorld;
    delete mptrBackground;
    delete mptrMountains_fg;
    delete mptrGround;
    delete mptrGrass;
    delete mptrCactus;
    delete mptrShip;
    delete mptrPlayer;
    mvecBlocks.clear();
    delete mptrRect1;
    delete mptrRect2;
}

void Level1State::Initialize()
{
    mptrBox2DWorld = new b2World(*new b2Vec2(0, 0.8f));
    SFMLDebugDraw* debugDraw = new SFMLDebugDraw(*Game::Instance()->GetRenderWindow());
    mptrBox2DWorld->SetDebugDraw(debugDraw);
    //debugDraw->SetFlags(b2Draw::e_shapeBit); //Only draw shapes

    mptrBackground = new ParallaxInfiniteScroller(Game::Instance()->GetRenderWindow(), "../Images/Parallax/sky.png", 0.05f, true);
    mptrMountains_fg = new ParallaxInfiniteScroller(Game::Instance()->GetRenderWindow(), "../Images/Parallax/mountains bg.png", 0.2f, true);
    mptrGround = new ParallaxInfiniteScroller(Game::Instance()->GetRenderWindow(), "../Images/Parallax/ground.png", 0.3f, true);
    mptrGrass = new ParallaxInfiniteScroller(Game::Instance()->GetRenderWindow(), "../Images/Parallax/grass2.png", 0.4f, true);
    mptrCactus = new ParallaxInfiniteScroller(Game::Instance()->GetRenderWindow(), "../Images/Parallax/cactus.png", 0.8f, true);
    mptrShip = new ParallaxInfiniteScroller(Game::Instance()->GetRenderWindow(), "../Images/Parallax/black-white-metro-viking-ship-icon.png", 0.95f, false);

    mptrShip->GetLeftAnimatedSprite()->SetPosition(700, 0);
    mptrShip->GetMiddleAnimatedSprite()->SetPosition(700, 0);
    mptrShip->GetRightAnimatedSprite()->SetPosition(700, 0);
    
    mptrPlayer = new PlayerCharacter(Game::Instance()->GetRenderWindow(), mptrBox2DWorld, 200, 10);    
    
                

    mvecBlocks.push_back(new PhysicsBlock(Game::Instance()->GetRenderWindow(), "C:\\Users\\Marius\\source\\repos\\GithubGameOff2017\\Images\\tile.png", mptrBox2DWorld, b2BodyType::b2_staticBody, 200, 600));
    mvecBlocks.push_back(new PhysicsBlock(Game::Instance()->GetRenderWindow(), "C:\\Users\\Marius\\source\\repos\\GithubGameOff2017\\Images\\tile.png", mptrBox2DWorld, b2BodyType::b2_staticBody, 300, 600));
    mvecBlocks.push_back(new PhysicsBlock(Game::Instance()->GetRenderWindow(), "C:\\Users\\Marius\\source\\repos\\GithubGameOff2017\\Images\\tile.png", mptrBox2DWorld, b2BodyType::b2_staticBody, 500, 700));
    mvecBlocks.push_back(new PhysicsBlock(Game::Instance()->GetRenderWindow(), "C:\\Users\\Marius\\source\\repos\\GithubGameOff2017\\Images\\tile.png", mptrBox2DWorld, b2BodyType::b2_staticBody, 600, 700));
    mvecBlocks.push_back(new PhysicsBlock(Game::Instance()->GetRenderWindow(), "C:\\Users\\Marius\\source\\repos\\GithubGameOff2017\\Images\\tile.png", mptrBox2DWorld, b2BodyType::b2_staticBody, 700, 700));
    
    

    /*sf::Font* font = AssetManager::Instance()->GetFont("../KeepCalm-Medium.ttf");
    sf::Text debugText;    
    debugText.setCharacterSize(24);
    debugText.setFont(*font);
    debugText.setPosition(30, 30);*/



    mptrGrass->GetLeftAnimatedSprite()->SetPosition(sf::Vector2f(mptrGrass->GetLeftAnimatedSprite()->GetPosition().x, 550));
    mptrGrass->GetMiddleAnimatedSprite()->SetPosition(sf::Vector2f(mptrGrass->GetMiddleAnimatedSprite()->GetPosition().x, 550));
    mptrGrass->GetRightAnimatedSprite()->SetPosition(sf::Vector2f(mptrGrass->GetRightAnimatedSprite()->GetPosition().x, 550));




    mptrRect1 = new OverlapCallbackRectangle(100, 100, 50, 50, overlapHandler, nullptr);
    mptrRect2 = new OverlapCallbackRectangle(140, 140, 50, 50, overlapHandler, nullptr);
    
}

void Level1State::Update(float dt)
{
    OverlapCallbackRectangleManager::Instance()->Update();

    mptrBackground->RearangeSpritesBasedOnCameraPosition();
    mptrMountains_fg->RearangeSpritesBasedOnCameraPosition();
    mptrGround->RearangeSpritesBasedOnCameraPosition();
    mptrGrass->RearangeSpritesBasedOnCameraPosition();
    mptrCactus->RearangeSpritesBasedOnCameraPosition();
    mptrShip->RearangeSpritesBasedOnCameraPosition();

    for (auto block : mvecBlocks)
    {
        block->Update();
    }

    mptrBox2DWorld->Step(1.0f/60.0f, 6, 6);
    mptrPlayer->Update(dt);
}

void Level1State::Draw(sf::RenderWindow & target)
{
    mptrBackground->Draw(sf::RenderStates::Default);        
    mptrMountains_fg->Draw(sf::RenderStates::Default);
    mptrGround->Draw(sf::RenderStates::Default);

    for (auto block : mvecBlocks)
    {
        block->Draw(sf::RenderStates::Default);
    }

    mptrPlayer->Draw(sf::RenderStates::Default);
    
    mptrGrass->Draw(sf::RenderStates::Default);
    mptrCactus->Draw(sf::RenderStates::Default);
    mptrShip->Draw(sf::RenderStates::Default);


    for (auto rect: OverlapCallbackRectangleManager::Instance()->getRegisteredRectangles())
    {
        sf::RectangleShape shape;
        shape.setPosition(rect->getSFMLRectangle().left + (rect->getSFMLRectangle().width/2), rect->getSFMLRectangle().top + (rect->getSFMLRectangle().height/2));
        shape.setSize(sf::Vector2f(rect->getSFMLRectangle().width, rect->getSFMLRectangle().height));
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Yellow);
        shape.setOutlineThickness(1);
        target.draw(shape);
    }


    mptrBox2DWorld->DrawDebugData();
}

void Level1State::Pause()
{
}

void Level1State::Resume()
{
}

void Level1State::HandleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        mptrMountains_fg->MoveRight();
        mptrGround->MoveRight();
        mptrGrass->MoveRight();
        mptrCactus->MoveRight();
        mptrShip->MoveRight();
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        mptrMountains_fg->MoveLeft();
        mptrGround->MoveLeft();
        mptrGrass->MoveLeft();
        mptrCactus->MoveLeft();
        mptrShip->MoveLeft();
    }

    mptrPlayer->HandleInput();
}
