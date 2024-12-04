#pragma once
#include "State.h"
#include "Game.h"
#include <memory>
#include <vector>
#include "Button.h"
#include "TextureManager.h"
#include "Grid.h"

using namespace std;

class GamePlay : public Engine::State
{
private:
	shared_ptr<Context> m_context;

	sf::RenderWindow window;

	//std::vector<std::vector<Tile>> grid;
	Grid grid;

	int gridSizeX = 18;
	int gridSizeY = 14;
	int tileSize = 32;
	int bombCount = 15;
	sf::Text endGameText;
	sf::Font endGameTextFont;

	bool gameOver = false;
	bool hasWon = false;

	sf::Clock gameOverTimer;
	bool startGameOverTimer = false;

	sf::Text timerText;
	sf::Font statsFont;
	int remainingFlags;
	sf::Text flagCounterText;

	int elapsedSeconds = 0;
	float elapsedTime = 0.0f;
	bool timerRunning = true;

	//Game logic
	void setUpEndGameText(const string& message);
	void checkGameState();

public:
	GamePlay(shared_ptr<Context>& context, int gridSizeX, int gridSizeY, int bombCount);
	//~mainMenu();

	void Init() override;
	void ProcessInput() override;
	void Update(const sf::Time& deltaTime) override;
	void Draw() override;


};

//class Game
//{
//public:
//    Game();
//    void run();
//
//private:
//    void handleEvents();
//    void update();
//    void render();
//    void checkWinCondition();
//
//    sf::RenderWindow window;
//    std::vector<std::vector<Tile>> grid;
//    const int gridSizeX = 18;
//    const int gridSizeY = 14;
//    const int tileSize = 32;
//    const int bombCount = 40;
//
//
//    bool gameOver = false;
//    bool hasWon = false;
//
//    void initializeGrid();
//    void placeBombs();
//    void countBombsAround();
//    void revealTile(int x, int y);
//    void displayEndGameText(const std::string& message);
//};
