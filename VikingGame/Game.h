#pragma once
#include <string>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "ParallaxInfiniteScroller.h"
#include "AnimatedSprite.h"
#include "PlayerCharacter.h"
#include "StateMachine.h"


class Game
{
private:
    Game(int width = 400, int height = 400);

public:
    
    ~Game();

    static Game* Instance(int width = 400, int height = 400);
    //b2World* GetBox2DWorld();    
    sf::View* GetCamera();
    StateMachine* GetStateMachine();
    sf::RenderWindow* GetRenderWindow();

    void Initialize();
    void Run();


private:
    bool mbIsRunning;
    int miWidth;
    int miHeight;

    sf::RenderWindow* mptrWindow;
    sf::View* mptrCamera;
        
    StateMachine* mptrStateMachine;


    void Loop();
};

