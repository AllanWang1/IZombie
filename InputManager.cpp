#include "InputManager.h"

namespace izombie
{
    // Effects: check if sprite was clicked by mouse
    bool InputManager::IsSpriteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow &window)
    {
        if (sf::Mouse::isButtonPressed(button)) {
            // Creates a rectangle that is formed by the sprite
            sf::IntRect spriteRect(sprite.getPosition().x, sprite.getPosition().y,
                                   sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
            // consider using GetMousePosition?
            return spriteRect.contains(sf::Mouse::getPosition(window));
        }
        return false;
    }

    // Effects: returns the position of the mouse
    sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow window)
    {
        return sf::Mouse::getPosition(window);
    }

}