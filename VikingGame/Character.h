#pragma once
#include "AnimatedSprite.h"
#include <map>

class Character
{
public:
    Character(sf::RenderWindow* renderWindow, b2World* ptrBox2DWorld);
    ~Character();

    AnimatedSprite* AddAnimatedSprite(std::string ID, float FPS);
    AnimatedSprite* GetAnimatedSpriteForID(std::string ID);

    void SetPosition(float x, float y);

    void SetCurrentAnimation(std::string animationID);
    std::string GetCurrentAnimation();

    void Jump();
    bool IsInAir();

    virtual void HandleInput() = 0;
    virtual void Update(float dt);
    void Draw(sf::RenderStates states);


    void RegisterForPhysics(b2World* ptrWorld, b2BodyType type, float mass, double posx, double posy);

    void SetPhysicsPosition(float x, float y);
    b2Vec2 GetPhysicsPosition();

    b2World* GetBox2DWorld();
    void DisablePhysics();
    void EnablePhysics();

    b2Body* getPhysicsBody() const;
    double getVelocity();

    std::vector<std::string> AnimationIDs() const;

    void IncFootContacts()
    {
        miFootContacts++;
    }

    void DecFootContacts()
    {
        miFootContacts--;
    }

private:    
    sf::RenderWindow* mptrRenderWindow;
    std::map<std::string, AnimatedSprite*> mmapAnimatedSprites;
    std::string mstrCurrentAnimationID;

    /* Box2D Physics */
    b2World* mptrBox2DWorld;
    b2Body* mptrb2Body;
    b2ChainShape* mptrb2ChainShape;
    b2Fixture* mptrFixture;

    int miFootContacts = 0;

    
  
public:
    class MyContactListener : public b2ContactListener
  {
  public:
      MyContactListener(Character* character)
      {
          mptrCharacter = character;
      }
      
      void BeginContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == 3 )
              mptrCharacter->IncFootContacts();
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == 3 )
              mptrCharacter->IncFootContacts();
      }
  
      void EndContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == 3 )
              mptrCharacter->DecFootContacts();
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == 3 )
              mptrCharacter->DecFootContacts();
      }

     private:
    Character* mptrCharacter;
  };

public:
    MyContactListener* mptrContactListener;

};




