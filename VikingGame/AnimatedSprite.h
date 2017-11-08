#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Box2D.h"

class AnimatedSprite
{
public:
    AnimatedSprite(sf::RenderWindow* renderWindow, float FPS);
    ~AnimatedSprite();

    void AddFrame(std::string filepath);
    void AddFrame(sf::Texture* texture);

    sf::Sprite* GetSFMLSprite(int index = 0);

    sf::Vector2f GetPosition();
    b2Vec2 GetPhysicsPosition();

    b2Body* GetPhysicsBody();

    void SetPosition(float x, float y);
    void SetPosition(sf::Vector2f position);
    void SetPhysicsPosition(float x, float y);

    void DisablePhysics();
    void EnablePhysics();

    void MoveToFirstFrame();
    // Unconditionally moves to the next frame
    void MoveToNextFrame();
    void Update(float dt);
    
    void Draw(sf::RenderStates states) const;

    // Creates the Box2D body, ChainShape, and fixture.
    void RegisterForPhysics(b2World* ptrWorld, b2BodyType type, std::vector<b2Vec2> chainVertices, float mass = 1);
    void PrintPhysics() const;

    int GetFrameCount() const;

private:
    std::vector<sf::Texture*> mvecFrameTextures;
    std::vector<sf::Sprite*> mvecFrameSprites;
    int miCurrentFrame;
    float mfTimeElapsedOnCurrentFrame;
    float mfFramesPerSecond;

    sf::RenderWindow* mptrRenderWindow;

    /* Box2D Physics */
    b2Body* mptrb2Body;
    b2ChainShape* mptrb2ChainShape;
    b2Fixture* mptrFixture;
};

