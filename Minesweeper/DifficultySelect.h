#pragma once
#include "State.h"
#include "Game.h"
#include <memory>
#include "Button.h"

using namespace std;

class DifficultySelect : public Engine::State
{
private:
	shared_ptr<Context> m_context;
	sf::Text selectTitle;
	sf::Font titleFont;
	Button easyButton;
	Button mediumButton;
	Button HardButton;
	Button backButton;

public:
	DifficultySelect(shared_ptr<Context>& context);
	//~mainMenu();

	void Init() override;
	void ProcessInput() override;
	void Update(const sf::Time& deltaTime) override;
	void Draw() override;
};




