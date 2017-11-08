#include "stdafx.h"
#include "ParallaxInfiniteScroller.h"
#include "AnimatedSprite.h"
#include "AssetManager.h"


ParallaxInfiniteScroller::ParallaxInfiniteScroller(sf::RenderWindow* renderWindow, const std::string backgroundImageFile, float fMovementMultiplier, bool repeat)
{
    mptrBackgroundTexture = AssetManager::Instance()->GetTexture(backgroundImageFile);

    mptrLeftSprite = new AnimatedSprite(renderWindow, 1);
    mptrLeftSprite->AddFrame(mptrBackgroundTexture);

    mptrMiddleSprite = new AnimatedSprite(renderWindow, 1);
    mptrMiddleSprite->AddFrame(mptrBackgroundTexture);

    mptrRightSprite = new AnimatedSprite(renderWindow, 1);
    mptrRightSprite->AddFrame(mptrBackgroundTexture);

    
    mptrLeftSprite->GetSFMLSprite(0)->setPosition(-(float)mptrBackgroundTexture->getSize().x, 0);
    mptrMiddleSprite->GetSFMLSprite(0)->setPosition(0, 0);
    mptrRightSprite->GetSFMLSprite(0)->setPosition(mptrBackgroundTexture->getSize().x, 0);

    mptrRenderWindow = renderWindow;
    //mView.reset(sf::FloatRect(0, 0, 1920, 1080));
    //mView.setCenter(sf::Vector2f(renderWindow->getView().getSize().x/2, renderWindow->getView().getSize().y/2));
    //mView.move(0, 300);

    mfMovementMultiplier = fMovementMultiplier;
    mbRepeat = repeat;
}


ParallaxInfiniteScroller::~ParallaxInfiniteScroller()
{
}

void ParallaxInfiniteScroller::MoveLeft()
{
    //mView.move(-0.6f * mfMovementMultiplier, 0);
    float x = mptrLeftSprite->GetPosition().x;
    float y = mptrLeftSprite->GetPosition().y;
    mptrLeftSprite->SetPosition(sf::Vector2f(x + (-0.6f * mfMovementMultiplier), y));

    x = mptrMiddleSprite->GetPosition().x;
    y = mptrMiddleSprite->GetPosition().y;
    mptrMiddleSprite->SetPosition(sf::Vector2f(x + (-0.6f * mfMovementMultiplier), y));

    x = mptrRightSprite->GetPosition().x;
    y = mptrRightSprite->GetPosition().y;
    mptrRightSprite->SetPosition(sf::Vector2f(x + (-0.6f * mfMovementMultiplier), y));
}

void ParallaxInfiniteScroller::MoveRight()
{
    //mView.move(0.6f * mfMovementMultiplier, 0);
    float x = mptrLeftSprite->GetPosition().x;
    float y = mptrLeftSprite->GetPosition().y;
    mptrLeftSprite->SetPosition(sf::Vector2f(x + (0.6f * mfMovementMultiplier), y));

    x = mptrMiddleSprite->GetPosition().x;
    y = mptrMiddleSprite->GetPosition().y;
    mptrMiddleSprite->SetPosition(sf::Vector2f(x + (0.6f * mfMovementMultiplier), y));

    x = mptrRightSprite->GetPosition().x;
    y = mptrRightSprite->GetPosition().y;
    mptrRightSprite->SetPosition(sf::Vector2f(x + (0.6f * mfMovementMultiplier), y));
}

void ParallaxInfiniteScroller::RearangeSpritesBasedOnCameraPosition()
{
    if (mbRepeat)
    {
        sf::View cameraView = mptrRenderWindow->getView();
        if (cameraView.getCenter().x <= mptrMiddleSprite->GetSFMLSprite(0)->getPosition().x)
        {
            // Take rightmost sprite and set its position to leftmost sprite - width.
            mptrRightSprite->GetSFMLSprite(0)->setPosition(mptrLeftSprite->GetSFMLSprite(0)->getPosition().x - mptrBackgroundTexture->getSize().x, mptrLeftSprite->GetSFMLSprite(0)->getPosition().y);

            auto oldLeftSprite = mptrLeftSprite;
            mptrLeftSprite = mptrRightSprite;
            mptrRightSprite = mptrMiddleSprite;
            mptrMiddleSprite = oldLeftSprite;
        }    

        if (cameraView.getCenter().x >= mptrMiddleSprite->GetSFMLSprite(0)->getPosition().x + mptrBackgroundTexture->getSize().x)
        {
            // Take leftmost sprite and set its position to rightmost sprite + width.
            mptrLeftSprite->GetSFMLSprite(0)->setPosition(mptrRightSprite->GetSFMLSprite(0)->getPosition().x + mptrBackgroundTexture->getSize().x, mptrRightSprite->GetSFMLSprite(0)->getPosition().y);

            auto oldRightSprite = mptrRightSprite;
            mptrRightSprite = mptrLeftSprite;
            mptrLeftSprite = mptrMiddleSprite;
            mptrMiddleSprite = oldRightSprite;
        }    
    }
}



void ParallaxInfiniteScroller::HandleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        MoveLeft();
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        MoveRight();
    }
}

void ParallaxInfiniteScroller::Draw(sf::RenderStates states) const
{
    //sf::View cameraView = mptrRenderWindow->getView();
    //sf::View localView = mView;
    //mptrRenderWindow->setView(cameraView);
    //localView.setCenter(localView.getCenter().x - cameraView.getCenter().x, localView.getCenter().y - cameraView.getCenter().y);
    //mptrRenderWindow->setView(localView);
    
    
    if (mbRepeat)
    {
        mptrRenderWindow->draw(*mptrLeftSprite->GetSFMLSprite(0), states);
        mptrRenderWindow->draw(*mptrMiddleSprite->GetSFMLSprite(0), states);
        mptrRenderWindow->draw(*mptrRightSprite->GetSFMLSprite(0), states);
    }else
    {
        mptrRenderWindow->draw(*mptrMiddleSprite->GetSFMLSprite(0), states);
    }

    //mptrRenderWindow->setView(cameraView);
}

AnimatedSprite * ParallaxInfiniteScroller::GetLeftAnimatedSprite()
{
    return mptrLeftSprite;
}

AnimatedSprite * ParallaxInfiniteScroller::GetMiddleAnimatedSprite()
{
    return mptrMiddleSprite;
}

AnimatedSprite * ParallaxInfiniteScroller::GetRightAnimatedSprite()
{
    return mptrRightSprite;
}

