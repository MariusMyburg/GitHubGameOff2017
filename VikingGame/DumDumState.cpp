#include "stdafx.h"
#include "DumDumState.h"
#include "AssetManager.h"
#include "Game.h"

DumDumState::DumDumState()
{
}


DumDumState::~DumDumState()
{
}

void DumDumState::Initialize()
{
    mBigFont = *AssetManager::Instance()->GetFont("../KeepCalm-Medium.ttf");    
    mBigText.setFont(mBigFont);
    mBigText.setCharacterSize(48);
    mBigText.setString("My Great Grandfather was a Viking");
    float width = mBigText.getCharacterSize();
    mBigText.setPosition((1920 / 2) - (width), (1080 / 2));

    mClock.restart();
}

void DumDumState::Update(float dt)
{
    sf::Time frameTime = mClock.restart();
    mRunTime += frameTime;

    if (mRunTime.asSeconds() >= 3)
    {
        Game::Instance()->GetStateMachine()->RemoveTopState();
    }
}

void DumDumState::Draw(sf::RenderWindow & target)
{
    target.draw(mBigText);
}

void DumDumState::Pause()
{
}

void DumDumState::Resume()
{
}

void DumDumState::HandleInput()
{
}
