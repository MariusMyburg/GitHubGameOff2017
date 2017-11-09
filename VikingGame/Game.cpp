#include "stdafx.h"
#include "Game.h"
#include "SfmlDebugDraw.h"
#include "../SFMLGUISystem/imgui.h"
#include "../SFMLGUISystem/imgui-SFML.h"
#include "PhysicsBlock.h"
#include "AssetManager.h"


Game::Game(int width, int height)
{
    miWidth = width;
    miHeight = height;
    mptrCamera = new sf::View(sf::Vector2f(width/2.0f, height/2.0f), sf::Vector2f(width, height));
    mptrStateMachine = new StateMachine();
    //mptrBox2DWorld = new b2World(*new b2Vec2(0, 1.1f));
}


Game::~Game()
{
}

Game * Game::Instance(int width, int height)
{
    static Game* instance = new Game(width, height);
    return instance;
}

//b2World * Game::GetBox2DWorld()
//{
//    return mptrBox2DWorld;
//}

//sf::View * Game::GetCamera()
//{
//    return mptrCamera;
//}

StateMachine * Game::GetStateMachine()
{
    return mptrStateMachine;
}

sf::RenderWindow * Game::GetRenderWindow()
{
    return mptrWindow;
}

void Game::Initialize()
{
    mptrWindow = new sf::RenderWindow();
    mptrWindow->create(sf::VideoMode(miWidth, miHeight, 32), "My Great Great Grandpa was a Viking", sf::Style::Fullscreen);
    //mptrWindow->setFramerateLimit(60);
}

void Game::Run()
{
    mbIsRunning = true;

    mptrWindow->display();

    sf::Font* font = AssetManager::Instance()->GetFont("../KeepCalm-Medium.ttf");
    sf::Text debugText;    
    debugText.setCharacterSize(24);
    debugText.setFont(*font);
    debugText.setPosition(30, 30);

    sf::Clock frameClock;

    while (mbIsRunning)
    {
        mbIsRunning = mptrWindow->isOpen();

        sf::Event event;

        while(mptrWindow->pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            

            switch (event.type)
            {
            case sf::Event::Closed:
                mptrWindow->close();
                break;

            default:
                break;
            }
        }

        sf::Time frameTime = frameClock.restart();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            mptrWindow->close();
        }
                
        mptrWindow->clear(sf::Color::Color(0, 0, 0));
        mptrWindow->setView(*mptrCamera);
        
        mptrStateMachine->GetActiveState()->HandleInput();
        mptrStateMachine->GetActiveState()->Update(frameTime.asSeconds());
        mptrStateMachine->GetActiveState()->Draw(*mptrWindow);
                
        mptrWindow->display();
    }


    delete mptrStateMachine;
}
