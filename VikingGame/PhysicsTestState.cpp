#include "stdafx.h"
#include "PhysicsTestState.h"
#include "AssetManager.h"
#include "Game.h"
#include "UnitsConversion.h"
#include "SfmlDebugDraw.h"

PhysicsTestState::PhysicsTestState()
{
}


PhysicsTestState::~PhysicsTestState()
{
}

void PhysicsTestState::Initialize()
{
    mBigFont = *AssetManager::Instance()->GetFont("../KeepCalm-Medium.ttf");    
    mBigText.setFont(mBigFont);
    mBigText.setCharacterSize(48);
    mBigText.setString("Physics Test");
    float width = mBigText.getCharacterSize();
    mBigText.setPosition(10, 10);


    mptrBox2DWorld = new b2World(b2Vec2(0, 9.8));
    
    SFMLDebugDraw* debugDraw = new SFMLDebugDraw(*Game::Instance()->GetRenderWindow());
    mptrBox2DWorld->SetDebugDraw(debugDraw);
    debugDraw->SetFlags(b2Draw::e_shapeBit); //Only draw shapes

    bodies.emplace_back(createBox(*mptrBox2DWorld,400,590,800,20,b2_staticBody));

    mClock.restart();
}

void PhysicsTestState::Update(float dt)
{
    sf::Time frameTime = mClock.restart();
    mRunTime += frameTime;

}

void PhysicsTestState::Draw(sf::RenderWindow & target)
{
    target.draw(mBigText);

 mptrBox2DWorld->Step(1.0/60,int32(8),int32(3));
 target.clear();
 for (b2Body* body=mptrBox2DWorld->GetBodyList(); body!=nullptr; body=body->GetNext())
 {
 sf::Shape* shape = static_cast<sf::Shape*>(body->GetUserData());
 shape->setPosition(unitsConversion::metersToPixels(body->GetPosition().x),
 unitsConversion::metersToPixels(body->GetPosition().y));
 shape->setRotation(unitsConversion::radToDeg<double>(body->GetAngle()));
 target.draw(*shape);
 }

 mptrBox2DWorld->DrawDebugData();
 //render.display();

}

void PhysicsTestState::Pause()
{
}

void PhysicsTestState::Resume()
{
}

void PhysicsTestState::HandleInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    {
     int x = sf::Mouse::getPosition(*Game::Instance()->GetRenderWindow()).x;
     int y = sf::Mouse::getPosition(*Game::Instance()->GetRenderWindow()).y;
     bodies.emplace_back(createBox(*mptrBox2DWorld,x,y,32,32));
    }
}




b2Body* PhysicsTestState::createBox(b2World& world,int pos_x,int pos_y, int size_x,int size_y,b2BodyType type)
{
 b2BodyDef bodyDef;
 bodyDef.position.Set(unitsConversion::pixelsToMeters<double>(pos_x),
 unitsConversion::pixelsToMeters<double>(pos_y));
 bodyDef.type = type;
 b2PolygonShape b2shape;
 b2shape.SetAsBox(unitsConversion::pixelsToMeters<double>(size_x/2.0),
 unitsConversion::pixelsToMeters<double>(size_y/2.0));
 b2FixtureDef fixtureDef;
 fixtureDef.density = 1.0;
 fixtureDef.friction = 0.4;
 fixtureDef.restitution= 0.5;
 fixtureDef.shape = &b2shape;

 b2Body* res = world.CreateBody(&bodyDef);
 res->CreateFixture(&fixtureDef);

 sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(size_x,size_y));
 shape->setOrigin(size_x/2.0,size_y/2.0);
 shape->setPosition(sf::Vector2f(pos_x,pos_y));

 if(type == b2_dynamicBody)
 shape->setFillColor(sf::Color::Blue);
 else
 shape->setFillColor(sf::Color::White);

 res->SetUserData(shape);

 return res;
}