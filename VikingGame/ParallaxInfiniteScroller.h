#pragma once
#include "SFML/Graphics.hpp"
#include "AnimatedSprite.h"
#include <vector>

class ParallaxInfiniteScroller
{
public:
    ParallaxInfiniteScroller(sf::RenderWindow* renderWindow, const std::string backgroundImageFile, float fMovementMultiplier, bool repeat);
    ~ParallaxInfiniteScroller();

    void MoveLeft();
    void MoveRight();
    void RearangeSpritesBasedOnCameraPosition();

    void HandleInput();
    void Draw(sf::RenderStates states) const;

    AnimatedSprite* GetLeftAnimatedSprite();
    AnimatedSprite* GetMiddleAnimatedSprite();
    AnimatedSprite* GetRightAnimatedSprite();

private:
    sf::Texture* mptrBackgroundTexture;
    bool            mbRepeat;
    AnimatedSprite* mptrLeftSprite;
    AnimatedSprite* mptrMiddleSprite;
    AnimatedSprite* mptrRightSprite;

    float mfMovementMultiplier;

    sf::RenderWindow* mptrRenderWindow;
    //sf::View mView;    
};

