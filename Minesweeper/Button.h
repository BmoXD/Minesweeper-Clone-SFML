#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
private:
    sf::Texture m_buttonTexture;
    sf::Sprite m_buttonSprite;
    sf::Text m_buttonText;
    sf::Font m_font;
    sf::Vector2f m_scale;
    sf::Vector2f m_textScale;
    sf::Vector2f m_hoverScale;
    sf::FloatRect buttonBounds;
    mutable sf::Cursor m_handCursor;
    mutable sf::Cursor m_defaultCursor;
    bool m_isHovered;
    bool m_isClicked;

public:
    Button();
    ~Button();

    // Initialize the button with a position, text, and font
    void Init(const std::string& text, sf::Vector2f position, sf::Vector2f scale);

    void CheckHover(const sf::Vector2i& mousePos, sf::RenderWindow& window);

    // Check if the button was clicked
    [[deprecated("Replaced by CheckHover")]]
    bool IsClicked(const sf::Vector2i& mousePos);

    bool getClickedStatus();

    // Draw the button
    void Draw(sf::RenderWindow& window) const;
};