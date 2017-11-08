#include "stdafx.h"
#include "AnimatedSprite.h"
#include "Game.h"

#include "SFMLDebugDraw.h"
#include "AssetManager.h"


AnimatedSprite::AnimatedSprite(sf::RenderWindow* renderWindow, float FPS)
{
    mptrRenderWindow = renderWindow;
    mfFramesPerSecond = FPS;
}


AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::AddFrame(std::string filepath)
{
    sf::Texture* newTexture = AssetManager::Instance()->GetTexture(filepath);
    mvecFrameTextures.push_back(newTexture);

    sf::Sprite* newSprite = new sf::Sprite(*newTexture);
    newSprite->setScale(1, 1);
    newSprite->setPosition(0, 0);
    mvecFrameSprites.push_back(newSprite);
}

void AnimatedSprite::AddFrame(sf::Texture* texture)
{    
    mvecFrameTextures.push_back(texture);

    sf::Sprite* newSprite = new sf::Sprite(*texture);
    newSprite->setScale(1, 1);
    newSprite->setPosition(0, 0);
    mvecFrameSprites.push_back(newSprite);
}

sf::Sprite* AnimatedSprite::GetSFMLSprite(int index)
{
    return mvecFrameSprites.at(index);
}

sf::Vector2f AnimatedSprite::GetPosition()
{
    return mvecFrameSprites.at(0)->getPosition();
}

b2Vec2 AnimatedSprite::GetPhysicsPosition()
{
    return mptrb2Body->GetPosition();
}

b2Body * AnimatedSprite::GetPhysicsBody()
{
    return mptrb2Body;
}

void AnimatedSprite::SetPosition(float x, float y)
{
    SetPosition(sf::Vector2f(x, y));
}

void AnimatedSprite::SetPosition(sf::Vector2f position)
{
    for (auto sprite: mvecFrameSprites)
    {
        sprite->setPosition(position);
    }
}

void AnimatedSprite::SetPhysicsPosition(float x, float y)
{
    if (mptrb2Body != nullptr)
    {
        mptrb2Body->SetTransform(b2Vec2(x, y), mptrb2Body->GetAngle());
    }
}

void AnimatedSprite::DisablePhysics()
{
    if (mptrb2Body != nullptr)
    {
        mptrb2Body->SetActive(false);
    }
}

void AnimatedSprite::EnablePhysics()
{
    if (mptrb2Body != nullptr)
    {
        mptrb2Body->SetActive(true);
    }
}

void AnimatedSprite::MoveToFirstFrame()
{
    mfTimeElapsedOnCurrentFrame = 0;
    miCurrentFrame = 0;
}

void AnimatedSprite::MoveToNextFrame()
{
    miCurrentFrame++;
    if (miCurrentFrame > mvecFrameSprites.size()-1)
    {
        miCurrentFrame = 0;
    }

    mfTimeElapsedOnCurrentFrame = 0;
}

void AnimatedSprite::Update(float dtSeconds)
{
    mfTimeElapsedOnCurrentFrame += dtSeconds;
    
    // Work out time required per frame, based on frames per second and number of frames.
    // Eg 10 frames / 2 frames per second = 5 
    float secondsPerFrame = (1.0 / (float)mvecFrameSprites.size()) / mfFramesPerSecond;

    // If elapsed time for this frame >= secondsPerFrame, advance the frame.
    if (mfTimeElapsedOnCurrentFrame >= secondsPerFrame)
    {        
        MoveToNextFrame();
    }

    // Match physics body position.
    if (mptrb2Body)
    {
        for (auto sprite: mvecFrameSprites)
        {
            sprite->setPosition(mptrb2Body->GetPosition().x - (sprite->getTexture()->getSize().x/2.0f), mptrb2Body->GetPosition().y - (sprite->getTexture()->getSize().y/2.0f));
        }
    }
}

void AnimatedSprite::Draw(sf::RenderStates states) const
{
    mptrRenderWindow->draw(*mvecFrameSprites.at(miCurrentFrame), states);    
}

void AnimatedSprite::RegisterForPhysics(b2World* ptrWorld, b2BodyType type, std::vector<b2Vec2> chainVertices, float mass)
{
    b2BodyDef def;
    def.gravityScale = 1.0f * mass;
    def.position.Set(mvecFrameTextures.at(0)->getSize().x / 2.0f, mvecFrameTextures.at(0)->getSize().y / 2.0f);
    def.type = type;    
    def.userData = this;    
    mptrb2Body = ptrWorld->CreateBody(&def);
    
    mptrb2ChainShape = new b2ChainShape();
    mptrb2ChainShape->CreateChain(&chainVertices[0], chainVertices.size());

    //b2CircleShape* circle = new b2CircleShape();
    //circle->m_radius = mvecFrameTextures.at(0)->getSize().x / 2.0f;

    //b2EdgeShape* edge = new b2EdgeShape();
    //edge->Set(chainVertices[0], chainVertices[1]);    

    b2FixtureDef fixtureDef;
    fixtureDef.shape = mptrb2ChainShape;
    fixtureDef.density = 1.0f;// * mass;    
    fixtureDef.userData = this;
    mptrFixture = mptrb2Body->CreateFixture(&fixtureDef);


    DisablePhysics();
}

void AnimatedSprite::PrintPhysics() const
{
    if (mptrb2Body)
    {
        printf("%f\n", mptrb2Body->GetPosition().y);
    }
}

int AnimatedSprite::GetFrameCount() const
{
    return mvecFrameSprites.size();
}
