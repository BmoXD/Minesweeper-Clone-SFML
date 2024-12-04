#include "DifficultySelect.h"
#include "MainMenu.h"
#include "GamePlay.h"
#include <iostream>


DifficultySelect::DifficultySelect(shared_ptr<Context>& context) : m_context(context)
{
}

void DifficultySelect::Init()
{
	int windowSizeX = m_context->m_window->getSize().x;
	int windowSizeY = m_context->m_window->getSize().y;

	titleFont.setSmooth(true);
	if (!titleFont.loadFromFile("../assets/fonts/DayDream.ttf"))
	{
		cerr << "Error loading font!" << std::endl;
		return;
	}
	selectTitle.setFont(titleFont);
	selectTitle.setString("Select Difficulty");
	selectTitle.setCharacterSize(45);
	selectTitle.setFillColor(sf::Color(202, 218, 222));

	selectTitle.setPosition(windowSizeX * 0.5, windowSizeY * 0.2);

	selectTitle.setOrigin(selectTitle.getLocalBounds().width / 2,
		selectTitle.getLocalBounds().height / 2);

	easyButton.Init("Easy", { windowSizeX * 0.5f, windowSizeY * 0.5f }, sf::Vector2f(1.7f, 1.7f));
	mediumButton.Init("Medium", { windowSizeX * 0.5f, windowSizeY * 0.65f }, sf::Vector2f(1.7f, 1.7f));
	HardButton.Init("Hard", { windowSizeX * 0.5f, windowSizeY * 0.80f }, sf::Vector2f(1.7f, 1.7f));
	backButton.Init("Back", { windowSizeX * 0.5f, windowSizeY * 0.92f }, sf::Vector2f(1.f, 1.f));
}

void DifficultySelect::ProcessInput()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*m_context->m_window);

	easyButton.CheckHover(mousePos, *m_context->m_window);
	mediumButton.CheckHover(mousePos, *m_context->m_window);
	HardButton.CheckHover(mousePos, *m_context->m_window);
	backButton.CheckHover(mousePos, *m_context->m_window);
}

void DifficultySelect::Update(const sf::Time& deltaTime)
{
	if (backButton.getClickedStatus())
	{
		m_context->m_states->Add(make_unique<MainMenu>(m_context), true);
	}
	else if (easyButton.getClickedStatus())
	{
		m_context->m_states->Add(make_unique<GamePlay>(m_context, 10, 8, 10), true); // Example: Easy grid size
	}
	else if (mediumButton.getClickedStatus())
	{
		m_context->m_states->Add(make_unique<GamePlay>(m_context, 18, 14, 40), true); // Example: Medium grid size
	}
	else if (HardButton.getClickedStatus())
	{
		m_context->m_states->Add(make_unique<GamePlay>(m_context, 24, 20, 60), true); // Example: Hard grid size
	}
}

void DifficultySelect::Draw()
{
	m_context->m_window->clear(sf::Color(83, 90, 102));
	m_context->m_window->draw(selectTitle);
	easyButton.Draw(*m_context->m_window);
	mediumButton.Draw(*m_context->m_window);
	HardButton.Draw(*m_context->m_window);
	backButton.Draw(*m_context->m_window);
	m_context->m_window->display();
}