#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Window/Event.hpp>
#include "MainMenu.h"
#include "GamePlay.h"

using namespace std;

Game::Game() : m_context(make_shared<Context>())
{
    m_context->m_window->create(sf::VideoMode(width, height), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
    //m_context->m_window->setKeyRepeatEnabled(false);
    m_context->m_states->Add(make_unique<MainMenu>(m_context));
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    bool mouseButtonPressed = false; // Track mouse button state to allow only single click actions

    while (m_context->m_window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        sf::Event event;
        while (m_context->m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_context->m_window->close();
        }

        // Handle mouse input here
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseButtonPressed)
        {
            mouseButtonPressed = true;

            if (!m_context->m_states->IsEmpty())
            {
                m_context->m_states->GetCurrent()->ProcessInput();  // Process the current state's input
            }
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !mouseButtonPressed)
        {
            mouseButtonPressed = true;

            if (!m_context->m_states->IsEmpty())
            {
                m_context->m_states->GetCurrent()->ProcessInput();  // Process the current state's input
            }
        }

        // Reset mouse button press state when the button is released
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            mouseButtonPressed = false;
        }

        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;

            m_context->m_states->ProcessStateChange();

            if (!m_context->m_states->IsEmpty())
            {
                m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
                m_context->m_states->GetCurrent()->Draw();
            }
            else
            {
                m_context->m_window->close();
            }
        }
    }
}
