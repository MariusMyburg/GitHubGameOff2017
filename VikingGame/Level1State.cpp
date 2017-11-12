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
    printf("Destructor.");

    delete mptrBox2DWorld;
    delete mptrBackground;
    //delete mptrMountains_fg;
    delete mptrGround;
    delete mptrGrass;
    //delete mptrCactus;
    //delete mptrShip;
    delete mptrPlayer;
    mvecBlocks.clear();
    delete mptrRect1;
    delete mptrRect2;
}

void Level1State::Initialize()
{
    mptrBox2DWorld = new b2World(*new b2Vec2(0, 0.1f));
    SFMLDebugDraw* debugDraw = new SFMLDebugDraw(*Game::Instance()->GetRenderWindow());
    mptrBox2DWorld->SetDebugDraw(debugDraw);
    //debugDraw->SetFlags(b2Draw::e_shapeBit); //Only draw shapes

    //mptrBackground = new ParallaxInfiniteScroller(Game::Instance()->GetRenderWindow(), "../Images/Parallax/sky.png", 0.05f, true);
    mptrBackground = new ParallaxInfiniteScroller(Game::Instance()->GetRenderWindow(), "C:/Users/Marius/Downloads/BG_Jungle_1_hor_rpt_Images/BG_Jungle_hor_rpt_1280x800.png", 0.05f, true);
    
    //mptrMountains_fg = new ParallaxInfiniteScroller(Game::Instance()->GetRenderWindow(), "../Images/Parallax/mountains bg.png", 0.2f, true);
    mptrGround = new ParallaxInfiniteScroller(Game::Instance()->GetRenderWindow(), "../Images/Parallax/ground.png", 1.3f, true);
    mptrGrass = new ParallaxInfiniteScroller(Game::Instance()->GetRenderWindow(), "../Images/Parallax/grass2.png", 2.4f, true);
    //mptrCactus = new ParallaxInfiniteScroller(Game::Instance()->GetRenderWindow(), "C:\\Users\\Marius\\Desktop\\GameArt_Processed\\craftpix-884412-runner-game-kit\\tileset\\tile-67.png", 5.8f, false);
    //mptrShip = new ParallaxInfiniteScroller(Game::Instance()->GetRenderWindow(), "../Images/Parallax/black-white-metro-viking-ship-icon.png", 0.95f, false);

    //mptrShip->GetLeftAnimatedSprite()->SetPosition(700, 0);
    //mptrShip->GetMiddleAnimatedSprite()->SetPosition(700, 0);
    //mptrShip->GetRightAnimatedSprite()->SetPosition(700, 0);
    
    mptrPlayer = new PlayerCharacter(Game::Instance()->GetRenderWindow(), mptrBox2DWorld, 200, 10);    
    
                

    mvecBlocks.push_back(new PhysicsBlock(Game::Instance()->GetRenderWindow(), "C:\\Users\\Marius\\Desktop\\GameArt_Processed\\craftpix-884412-runner-game-kit\\tileset\\tile-07.png", mptrBox2DWorld, b2BodyType::b2_staticBody, 200, 600));
    //mvecBlocks.push_back(new PhysicsBlock(Game::Instance()->GetRenderWindow(), "C:\\Users\\Marius\\source\\repos\\GithubGameOff2017\\Images\\tile.png", mptrBox2DWorld, b2BodyType::b2_staticBody, 300, 600));
    /*mvecBlocks.push_back(new PhysicsBlock(Game::Instance()->GetRenderWindow(), "C:\\Users\\Marius\\source\\repos\\GithubGameOff2017\\Images\\tile.png", mptrBox2DWorld, b2BodyType::b2_staticBody, 500, 700));
    mvecBlocks.push_back(new PhysicsBlock(Game::Instance()->GetRenderWindow(), "C:\\Users\\Marius\\source\\repos\\GithubGameOff2017\\Images\\tile.png", mptrBox2DWorld, b2BodyType::b2_staticBody, 600, 701));
    mvecBlocks.push_back(new PhysicsBlock(Game::Instance()->GetRenderWindow(), "C:\\Users\\Marius\\source\\repos\\GithubGameOff2017\\Images\\tile.png", mptrBox2DWorld, b2BodyType::b2_staticBody, 700, 702));

    mvecBlocks.push_back(new PhysicsBlock(Game::Instance()->GetRenderWindow(), "C:\\Users\\Marius\\source\\repos\\GithubGameOff2017\\Images\\tile.png", mptrBox2DWorld, b2BodyType::b2_staticBody, 930, 700));*/
    mvecBlocks.push_back(new PhysicsBlock(Game::Instance()->GetRenderWindow(), "C:\\Users\\Marius\\Desktop\\empty.png", mptrBox2DWorld, b2BodyType::b2_staticBody, 500, 700));
    mvecBlocks.push_back(new PhysicsBlock(Game::Instance()->GetRenderWindow(), "C:\\Users\\Marius\\Desktop\\empty.png", mptrBox2DWorld, b2BodyType::b2_staticBody, 500+1600, 700));

    
    

    /*sf::Font* font = AssetManager::Instance()->GetFont("../KeepCalm-Medium.ttf");
    sf::Text debugText;    
    debugText.setCharacterSize(24);
    debugText.setFont(*font);
    debugText.setPosition(30, 30);*/



    //mptrCactus->GetMiddleAnimatedSprite()->SetPosition(sf::Vector2f(300, mptrGrass->GetMiddleAnimatedSprite()->GetPosition().y));


    mptrGrass->GetLeftAnimatedSprite()->SetPosition(sf::Vector2f(mptrGrass->GetLeftAnimatedSprite()->GetPosition().x, 350));
    mptrGrass->GetMiddleAnimatedSprite()->SetPosition(sf::Vector2f(mptrGrass->GetMiddleAnimatedSprite()->GetPosition().x, 350));
    mptrGrass->GetRightAnimatedSprite()->SetPosition(sf::Vector2f(mptrGrass->GetRightAnimatedSprite()->GetPosition().x, 350));


/*  mptrRect1 = new OverlapCallbackRectangle(100, 100, 50, 50, overlapHandler, nullptr);
    mptrRect2 = new OverlapCallbackRectangle(140, 140, 50, 50, overlapHandler, nullptr);*/
    
}

void Level1State::Update(float dt)
{
    OverlapCallbackRectangleManager::Instance()->Update();

    mptrBackground->RearangeSpritesBasedOnCameraPosition();
    //mptrMountains_fg->RearangeSpritesBasedOnCameraPosition();
    mptrGround->RearangeSpritesBasedOnCameraPosition();
    mptrGrass->RearangeSpritesBasedOnCameraPosition();
    //mptrCactus->RearangeSpritesBasedOnCameraPosition();
    //mptrShip->RearangeSpritesBasedOnCameraPosition();

    for (auto block : mvecBlocks)
    {
        block->Update();
    }

    mptrBox2DWorld->Step(1.0f/60.0f, 6, 6);
    mptrPlayer->Update(dt);

    Game::Instance()->GetCamera()->setCenter(mptrPlayer->GetAnimatedSpriteForID(mptrPlayer->GetCurrentAnimation())->GetPosition().x, Game::Instance()->getHeight()/2.f);



    // If we fell, re-initialize level.
    if (mptrPlayer->GetAnimatedSpriteForID(mptrPlayer->GetCurrentAnimation())->GetPosition().y > 2000)
    {
        Initialize();
    }
}

void Level1State::Draw(sf::RenderWindow & target)
{
    mptrBackground->Draw(sf::RenderStates::Default);        
    //mptrMountains_fg->Draw(sf::RenderStates::Default);
    mptrGround->Draw(sf::RenderStates::Default);

    for (auto block : mvecBlocks)
    {
        block->Draw(sf::RenderStates::Default);
    }

    mptrPlayer->Draw(sf::RenderStates::Default);
    
    mptrGrass->Draw(sf::RenderStates::Default);
    //mptrCactus->Draw(sf::RenderStates::Default);
    //mptrShip->Draw(sf::RenderStates::Default);


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
        //mptrMountains_fg->MoveRight();
        mptrGround->MoveRight();
        mptrGrass->MoveRight();
        //mptrCactus->MoveRight();
        //mptrShip->MoveRight();
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        //mptrMountains_fg->MoveLeft();
        mptrGround->MoveLeft();
        mptrGrass->MoveLeft();
        //mptrCactus->MoveLeft();
        //mptrShip->MoveLeft();
    }

    mptrPlayer->HandleInput();
}
