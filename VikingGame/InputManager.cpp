#include "stdafx.h"
#include "InputManager.h"

bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow & window)
{
    if (sf::Mouse::isButtonPressed(button))
    {
        sf::IntRect buttonRect(object.getPosition().x, object.getPosition().y,
            object.getGlobalBounds().width, object.getGlobalBounds().height);

        if (buttonRect.contains(sf::Mouse::getPosition()))
        {
            return true;
        }
    }

    return false;
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow & window)
{
    return sf::Mouse::getPosition();
}
