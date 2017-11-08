#include "stdafx.h"
#include "Character.h"
#include "Game.h"
#include "SfmlDebugDraw.h"


Character::Character(sf::RenderWindow* renderWindow, b2World* ptrBox2DWorld)
{
    mptrBox2DWorld = ptrBox2DWorld;
    mptrRenderWindow = renderWindow;
}


Character::~Character()
{
}

AnimatedSprite * Character::AddAnimatedSprite(std::string ID, float FPS)
{
    AnimatedSprite* newAnimatedSprite = new AnimatedSprite(mptrRenderWindow, FPS);
    mmapAnimatedSprites.insert(std::pair<std::string, AnimatedSprite*>(ID, newAnimatedSprite));

    if (mstrCurrentAnimationID == "")
    {
        mstrCurrentAnimationID = ID;
    }

    return newAnimatedSprite;
}

AnimatedSprite * Character::GetAnimatedSpriteForID(std::string ID)
{
    return mmapAnimatedSprites[ID];
}

void Character::SetPosition(float x, float y)
{
    for(auto sprite : mmapAnimatedSprites)
    {
        sprite.second->SetPosition(sf::Vector2f(x, y));
        sprite.second->SetPhysicsPosition(x, y);
    }

    SetPhysicsPosition(x, y);
}

void Character::SetCurrentAnimation(std::string animationID)
{
    if (mstrCurrentAnimationID != animationID)
    {
       // AnimatedSprite* prevAnimatedSptire = mmapAnimatedSprites[mstrCurrentAnimationID];
        mstrCurrentAnimationID = animationID;
    
        for(auto sprite : mmapAnimatedSprites)
        {
            sprite.second->MoveToFirstFrame();
            sprite.second->DisablePhysics();            
        }

        //SetPhysicsPosition(prevAnimatedSptire->GetPhysicsPosition().x, prevAnimatedSptire->GetPhysicsPosition().y);
        EnablePhysics();
    }

    
}

std::string Character::GetCurrentAnimation()
{
    return mstrCurrentAnimationID;
}

void Character::Jump()
{
    //to change velocity by 10
    b2Body* body = mptrb2Body; //GetAnimatedSpriteForID(mstrCurrentAnimationID)->GetPhysicsBody();
    if (!IsInAir())
    {
        float impulse = body->GetMass() * 1;
        body->ApplyLinearImpulse(b2Vec2(0,-impulse), body->GetWorldCenter(), true);
    }
}

bool Character::IsInAir()
{
    b2Body* body = mptrb2Body; //GetAnimatedSpriteForID(mstrCurrentAnimationID)->GetPhysicsBody();
    return (body->GetLinearVelocity().y != 0);
}

void Character::Update(float dt)
{
    GetAnimatedSpriteForID(mstrCurrentAnimationID)->Update(dt);

    // Match physics body position.
    if (mptrb2Body)
    {
        //GetAnimatedSpriteForID(mstrCurrentAnimationID)->SetPosition(mptrb2Body->GetPosition().x*sfdd::PIXELS_PER_METER, mptrb2Body->GetPosition().y*sfdd::PIXELS_PER_METER);        

        for (int i = 0; i < GetAnimatedSpriteForID(mstrCurrentAnimationID)->GetFrameCount(); i++)
        {
            GetAnimatedSpriteForID(mstrCurrentAnimationID)->GetSFMLSprite(i)->setOrigin(
            GetAnimatedSpriteForID(mstrCurrentAnimationID)->GetSFMLSprite(i)->getTexture()->getSize().x/2.0f,
            GetAnimatedSpriteForID(mstrCurrentAnimationID)->GetSFMLSprite(i)->getTexture()->getSize().y/2.0f);

            GetAnimatedSpriteForID(mstrCurrentAnimationID)->GetSFMLSprite(i)->setPosition(
            (mptrb2Body->GetPosition().x*sfdd::PIXELS_PER_METER),
            (mptrb2Body->GetPosition().y*sfdd::PIXELS_PER_METER));
        }
    }
}

void Character::Draw(sf::RenderStates states)
{
    GetAnimatedSpriteForID(mstrCurrentAnimationID)->Draw(states);
}


void Character::RegisterForPhysics(b2World* ptrWorld, b2BodyType type, float mass, double posx, double posy)
{
    mptrBox2DWorld = ptrWorld;

    //b2BodyDef def;
    //def.gravityScale = 1.0f * mass;
    ////def.position.Set(mmapAnimatedSprites[GetCurrentAnimation()]->GetSFMLSprite(0)->getTexture()->getSize().x / 2.0f, mmapAnimatedSprites[GetCurrentAnimation()]->GetSFMLSprite(0)->getTexture()->getSize().y / 2.0f);
    //def.position.Set(posx/sfdd::PIXELS_PER_METER, posy/sfdd::PIXELS_PER_METER);
    //
    //def.type = type;    
    //def.userData = this;    
    //def.awake = true;
    ////def.allowSleep = false;
    //mptrb2Body = ptrWorld->CreateBody(&def);
    //
    //
    //mptrb2ChainShape = new b2ChainShape();
    //mptrb2ChainShape->CreateChain(&chainVertices[0], chainVertices.size());

    //b2FixtureDef fixtureDef;
    //fixtureDef.shape = mptrb2ChainShape;
    //fixtureDef.density = 1.0f;// * mass;    
    //fixtureDef.userData = this;
    //mptrFixture = mptrb2Body->CreateFixture(&fixtureDef);

    auto texture = mmapAnimatedSprites[GetCurrentAnimation()]->GetSFMLSprite(0)->getTexture();

    b2BodyDef def;
    def.gravityScale = 1.0f;
    def.position.Set(posx/sfdd::PIXELS_PER_METER, posy/sfdd::PIXELS_PER_METER);
    def.type = type;
    def.userData = this;    
    mptrb2Body = ptrWorld->CreateBody(&def);

    b2PolygonShape* shape = new b2PolygonShape();
    float x = texture->getSize().x;
    float y = texture->getSize().y;
    shape->SetAsBox((x/sfdd::PIXELS_PER_METER)/2.0f, (y/sfdd::PIXELS_PER_METER)/2.0f);    
    //shape->SetAsBox(2, 2);    
    //mptrb2Shape = shape;
        
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 1;    
    //fixtureDef.restitution = 0.8f;
    fixtureDef.userData = this;
    mptrFixture = mptrb2Body->CreateFixture(&fixtureDef);


    DisablePhysics();
}

void Character::SetPhysicsPosition(float x, float y)
{
    mptrb2Body->SetTransform(b2Vec2(x, y), mptrb2Body->GetAngle());
    mptrb2Body->SetAwake(true);
}

b2Vec2 Character::GetPhysicsPosition()
{
    return mptrb2Body->GetTransform().p;
}

b2World * Character::GetBox2DWorld()
{
    return mptrBox2DWorld;
}

void Character::DisablePhysics()
{
    mptrb2Body->SetActive(false);
}

void Character::EnablePhysics()
{
    mptrb2Body->SetActive(true);
}

std::vector<std::string> Character::AnimationIDs() const
{
    std::vector<std::string> result;

    for (auto kvp : mmapAnimatedSprites)
    {
        result.push_back(kvp.first);
    }

    return result;
}
