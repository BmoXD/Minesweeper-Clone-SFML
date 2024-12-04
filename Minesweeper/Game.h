#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include "StateMan.h"

#include <memory>

using namespace std;

struct Context
{
	unique_ptr<Engine::StateMan> m_states;
	unique_ptr<sf::RenderWindow> m_window;

	Context()
	{
		m_states = make_unique <Engine::StateMan>();
		m_window = make_unique <sf::RenderWindow>();
	}
};

class Game
{
private:
	shared_ptr<Context> m_context;
	const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 15.f);

	static const int width = 800;
	static const int height = 640;
	


public:
	Game();

	static sf::Vector2u getDefaultWindowSize() { return sf::Vector2u(width, height); };

	void run();
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
