#include "Button.h"
#include <iostream>

using namespace std;

Button::Button() : m_isHovered(false), m_isClicked(false)
{
    m_font.loadFromFile("../assets/fonts/Minecraft.ttf");
    m_buttonTexture.loadFromFile("../assets/button.png");

    m_handCursor.loadFromSystem(sf::Cursor::Hand);
    m_defaultCursor.loadFromSystem(sf::Cursor::Arrow);
}

Button::~Button() {}

void Button::Init(const std::string& text, sf::Vector2f position, sf::Vector2f scale)
{
    m_scale = scale;
    m_hoverScale = { 1.2f, 1.2f };
    m_buttonSprite.setTexture(m_buttonTexture);
    buttonBounds = m_buttonSprite.getLocalBounds();
    m_buttonSprite.setPosition(position);
    m_buttonSprite.setScale(scale);
    m_buttonSprite.setOrigin(buttonBounds.width / 2, buttonBounds.height / 2);
    cout << buttonBounds.width << endl;
    cout << buttonBounds.height << endl;

    m_buttonText.setFont(m_font);
    m_buttonText.setString(text);
    m_buttonText.setCharacterSize(25 * scale.x);
    m_buttonText.setFillColor(sf::Color::Black);
    m_buttonText.setOrigin(m_buttonText.getLocalBounds().width / 2, m_buttonText.getLocalBounds().height / 1.3);
    m_buttonText.setPosition(position.x , position.y);
    m_textScale = m_buttonText.getScale();
}

void Button::CheckHover(const sf::Vector2i& mousePos, sf::RenderWindow& window)
{
    sf::FloatRect buttonGlobalBounds = m_buttonSprite.getGlobalBounds();

    // If the mouse is over the button
    if (buttonGlobalBounds.contains(static_cast<sf::Vector2f>(mousePos)))
    {
        window.setMouseCursor(m_handCursor);

        if (!m_isHovered) // Only change scale if hover state is new
        {
            m_buttonSprite.setScale(m_buttonSprite.getScale().x * m_hoverScale.x, m_buttonSprite.getScale().y * m_hoverScale.y); // Scale up
            m_buttonText.setScale(m_textScale.x * m_hoverScale.x, m_textScale.y * m_hoverScale.y);
            m_isHovered = true;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            cout << buttonGlobalBounds.contains(static_cast<sf::Vector2f>(mousePos)) << endl;
            m_isClicked = true;
            cout << "Button clicked!";
        }
    }
    else
    {
        window.setMouseCursor(m_defaultCursor);

        if (m_isHovered) // Reset scale when hover ends
        {
            m_buttonSprite.setScale(m_scale); // Scale back to original
            m_buttonText.setScale(m_textScale);
            m_isHovered = false;
        }
    }
}

[[deprecated("Replaced by CheckHover")]]
bool Button::IsClicked(const sf::Vector2i& mousePos)
{
    sf::FloatRect buttonGlobalBounds = m_buttonSprite.getGlobalBounds();
    if (buttonGlobalBounds.contains(static_cast<sf::Vector2f>(mousePos)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        cout << buttonGlobalBounds.contains(static_cast<sf::Vector2f>(mousePos)) << endl;
        m_isClicked = true;
        cout << "Button clicked!";
        return true;
    }
    m_isClicked = false;
    return false;
}

bool Button::getClickedStatus()
{
    return m_isClicked;
}

void Button::Draw(sf::RenderWindow& window) const
{
    window.draw(m_buttonSprite);
    window.draw(m_buttonText);
}
