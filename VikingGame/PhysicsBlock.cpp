#include "stdafx.h"
#include "PhysicsBlock.h"
#include "AssetManager.h"
#include "Game.h"
#include "UnitsConversion.h"
#include "SFMLDebugDraw.h"

PhysicsBlock::PhysicsBlock(sf::RenderWindow* renderWindow, std::string filename, b2World* b2world, b2BodyType bodyType, double posx, double posy)
{
    mptrRenderWindow = renderWindow;

    sf::Texture* texture = AssetManager::Instance()->GetTexture(filename);
    mptrSprite = new AnimatedSprite(renderWindow, 1);
      
    mptrSprite->AddFrame(texture);

    mb2BodyType = bodyType;

    b2BodyDef def;
    def.gravityScale = 1.0f;
    def.position.Set(posx/sfdd::PIXELS_PER_METER, posy/sfdd::PIXELS_PER_METER);
    def.type = bodyType;
    def.userData = this;    
    mptrb2Body = b2world->CreateBody(&def);

    b2PolygonShape* shape = new b2PolygonShape();
    float x = texture->getSize().x;
    float y = texture->getSize().y;
    shape->SetAsBox((x/sfdd::PIXELS_PER_METER)/2.0f, (y/sfdd::PIXELS_PER_METER)/2.0f);    
    //shape->SetAsBox(2, 2);    
    mptrb2Shape = shape;
        
    b2FixtureDef fixtureDef;
    fixtureDef.shape = mptrb2Shape;
    fixtureDef.density = 1;    
    //fixtureDef.restitution = 0.8f;
    fixtureDef.friction = 0.0f;
    fixtureDef.userData = this;
    mptrFixture = mptrb2Body->CreateFixture(&fixtureDef);
}

PhysicsBlock::~PhysicsBlock()
{
}

sf::Vector2f PhysicsBlock::GetPosition()
{
    return mptrSprite->GetSFMLSprite(0)->getPosition();
}

void PhysicsBlock::SetPosition(sf::Vector2f position)
{
    mptrSprite->GetSFMLSprite(0)->setPosition(position);
}

void PhysicsBlock::SetPhysicsPosition(float x, float y)
{
    mptrb2Body->SetTransform(b2Vec2(
        (x/sfdd::PIXELS_PER_METER), 
        (y/sfdd::PIXELS_PER_METER)), 
        mptrb2Body->GetAngle());
}

void PhysicsBlock::Update()
{
    // Match physics body position.
    if (mptrb2Body)
    {
        mptrSprite->GetSFMLSprite(0)->setOrigin(
            mptrSprite->GetSFMLSprite(0)->getTexture()->getSize().x/2.0f,
            mptrSprite->GetSFMLSprite(0)->getTexture()->getSize().y/2.0f);

        mptrSprite->GetSFMLSprite(0)->setPosition(
            (mptrb2Body->GetPosition().x*sfdd::PIXELS_PER_METER),
            (mptrb2Body->GetPosition().y*sfdd::PIXELS_PER_METER));
    }
}

void PhysicsBlock::Draw(sf::RenderStates states) const
{
    mptrSprite->Draw(states);    
}
