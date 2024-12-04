#include "MainMenu.h"
#include "DifficultySelect.h"
#include <iostream>


MainMenu::MainMenu(shared_ptr<Context>& context) : m_context(context)
{
	
}

void MainMenu::Init()
{
	int windowSizeX = m_context->m_window->getSize().x;
	int windowSizeY = m_context->m_window->getSize().y;

	titleFont.setSmooth(true);
	if (!titleFont.loadFromFile("../assets/fonts/DayDream.ttf"))
	{
	    cerr << "Error loading font!" << std::endl;
	    return;
	}
	gameTitle.setFont(titleFont);
	gameTitle.setString("MineSweeper");
	gameTitle.setCharacterSize(60);
	gameTitle.setFillColor(sf::Color(202, 218, 222));

	gameTitle.setPosition(windowSizeX * 0.5, windowSizeY * 0.2);

	gameTitle.setOrigin(gameTitle.getLocalBounds().width / 2,
		gameTitle.getLocalBounds().height / 2);

	playButton.Init("Play", { windowSizeX * 0.5f, windowSizeY * 0.6f }, sf::Vector2f(1.7f, 1.7f));
	exitButton.Init("Exit", { windowSizeX * 0.5f, windowSizeY * 0.75f }, sf::Vector2f(1.7f, 1.7f));
}

void MainMenu::ProcessInput()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*m_context->m_window);

	// Handle hover effect for buttons
	playButton.CheckHover(mousePos, *m_context->m_window);
	exitButton.CheckHover(mousePos, *m_context->m_window);

	//// Handle button click for Exit
	//exitButton.IsClicked(mousePos);

	//// Handle button click for Play
	//if (playButton.IsClicked(mousePos))
	//{
	//	std::cout << "Play Button Clicked!" << std::endl;
	//	// Transition to the game state (or another state)
	//}
}

void MainMenu::Update(const sf::Time& deltaTime)
{
	if (playButton.getClickedStatus())
	{
		m_context->m_states->Add(make_unique<DifficultySelect>(m_context), true);
	}

	if (exitButton.getClickedStatus())
	{
		m_context->m_window->close();
	}
}

void MainMenu::Draw()
{
	m_context->m_window->clear(sf::Color(83, 90, 102));
	m_context->m_window->draw(gameTitle);
	playButton.Draw(*m_context->m_window);
	exitButton.Draw(*m_context->m_window);
	m_context->m_window->display();
}