#include "EndScreen.h"
#include "MainMenu.h"
#include <iostream>

EndScreen::EndScreen(shared_ptr<Context>& context, bool hasWon, string time) : m_context(context), hasWon(hasWon), time(time)
{
	m_context->m_window->setSize(Game::getDefaultWindowSize());
	sf::View newView(sf::FloatRect(0.f, 0.f, Game::getDefaultWindowSize().x, Game::getDefaultWindowSize().y));
	m_context->m_window->setView(newView);
}

void EndScreen::Init()
{
	int windowSizeX = m_context->m_window->getSize().x;
	int windowSizeY = m_context->m_window->getSize().y;

	font.setSmooth(true);
	if (!font.loadFromFile("../assets/fonts/DayDream.ttf"))
	{
		cerr << "Error loading font!" << std::endl;
		return;
	}
	endGameText.setFont(font);
	endGameText.setString(hasWon == true ? "Mines cleared!" : "You exploded!");
	endGameText.setCharacterSize(45);
	endGameText.setFillColor(sf::Color(202, 218, 222));
	endGameText.setOrigin(endGameText.getLocalBounds().width / 2, endGameText.getLocalBounds().height / 2);
	endGameText.setPosition(windowSizeX * 0.5, windowSizeY * 0.2);


	timerText.setFont(font);
	timerText.setString(time);
	timerText.setCharacterSize(45);
	timerText.setFillColor(sf::Color(202, 218, 222));
	timerText.setOrigin(endGameText.getLocalBounds().width / 2, endGameText.getLocalBounds().height / 2);
	timerText.setPosition(windowSizeX * 0.5, windowSizeY * 0.3);



	menuButton.Init("Go Back", { windowSizeX * 0.5f, windowSizeY * 0.65f }, sf::Vector2f(1.7f, 1.7f));
}

void EndScreen::ProcessInput()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*m_context->m_window);

	menuButton.CheckHover(mousePos, *m_context->m_window);
}

void EndScreen::Update(const sf::Time& deltaTime)
{
	if (menuButton.getClickedStatus())
	{
		m_context->m_states->Add(make_unique<MainMenu>(m_context), true);
	}
}

void EndScreen::Draw()
{
	m_context->m_window->clear(sf::Color(83, 90, 102));
	m_context->m_window->draw(endGameText);
	menuButton.Draw(*m_context->m_window);
	m_context->m_window->display();
}