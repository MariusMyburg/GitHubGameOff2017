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
    
        for (auto animID: AnimationIDs())
        {
            for (int i = 0; i < GetAnimatedSpriteForID(animID)->GetFrameCount(); i++)
        {
            GetAnimatedSpriteForID(animID)->GetSFMLSprite(i)->setOrigin(
            GetAnimatedSpriteForID(animID)->GetSFMLSprite(i)->getTexture()->getSize().x/2.0f,
            GetAnimatedSpriteForID(animID)->GetSFMLSprite(i)->getTexture()->getSize().y/2.0f);

            GetAnimatedSpriteForID(animID)->GetSFMLSprite(i)->setPosition(
            (mptrb2Body->GetPosition().x*sfdd::PIXELS_PER_METER),
            (mptrb2Body->GetPosition().y*sfdd::PIXELS_PER_METER));
        }
        }

        for(auto sprite : mmapAnimatedSprites)
        {
            sprite.second->MoveToFirstFrame();
            sprite.second->DisablePhysics();            
        }

        EnablePhysics();
    }

    
}

std::string Character::GetCurrentAnimation()
{
    return mstrCurrentAnimationID;
}

void Character::Jump()
{    
    b2Body* body = mptrb2Body;
    if (!IsInAir())
    {
        float impulse = body->GetMass() * 0.05;
        body->ApplyLinearImpulse(b2Vec2(0,-impulse), body->GetWorldCenter(), true);
    }
}

bool Character::IsInAir()
{
    return miFootContacts == 0;
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
    
    auto texture = mmapAnimatedSprites[GetCurrentAnimation()]->GetSFMLSprite(0)->getTexture();

    b2BodyDef def;
    def.gravityScale = 1.0f;
    def.position.Set(posx/sfdd::PIXELS_PER_METER, posy/sfdd::PIXELS_PER_METER);
    def.type = type;
    def.userData = this;    
    def.fixedRotation = true;
    def.linearDamping = 1.0f;
    mptrb2Body = ptrWorld->CreateBody(&def);

    b2PolygonShape* shape = new b2PolygonShape();
    float x = texture->getSize().x;
    float y = texture->getSize().y-20;
    shape->SetAsBox((x/sfdd::PIXELS_PER_METER)/2.0f, (y/sfdd::PIXELS_PER_METER)/2.0f);    
        
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 1;    
    fixtureDef.userData = this;    
    mptrFixture = mptrb2Body->CreateFixture(&fixtureDef);


    b2CircleShape* circle = new b2CircleShape();
    circle->m_radius = 0.1;
    circle->m_p.y = 0.07f;
    
    fixtureDef.shape = circle;
    fixtureDef.density = 1;
    mptrb2Body->CreateFixture(&fixtureDef);


    //add foot sensor fixture
    b2PolygonShape polygonShape;
      polygonShape.SetAsBox(0.1, 0.02, b2Vec2(0,0.2), 0);
      fixtureDef.isSensor = true;
      fixtureDef.shape = &polygonShape;
      b2Fixture* footSensorFixture = mptrb2Body->CreateFixture(&fixtureDef);
      footSensorFixture->SetUserData( (void*)3 );


    mptrContactListener = new Character::MyContactListener(this);


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

b2Body * Character::getPhysicsBody() const
{
    return mptrb2Body;
}

double Character::getVelocity()
{
    return getPhysicsBody()->GetLinearVelocity().x;
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
