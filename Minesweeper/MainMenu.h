#pragma once

#include "State.h"
#include "Game.h"
#include <memory>
#include "Button.h"

using namespace std;

class MainMenu : public Engine::State
{
private:
	shared_ptr<Context> m_context;
	sf::Text gameTitle;
	sf::Font titleFont;
	Button playButton;
	Button exitButton;

public:
	MainMenu(shared_ptr<Context> &context);
	//~mainMenu();

	void Init() override;
	void ProcessInput() override;
	void Update(const sf::Time& deltaTime) override;
	void Draw() override;
};

