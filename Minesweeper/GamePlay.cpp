#include "GamePlay.h"
#include "EndScreen.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

GamePlay::GamePlay(std::shared_ptr<Context>& context, int gridSizeX, int gridSizeY, int bombCount)
    : m_context(context), grid(gridSizeX, gridSizeY, 32, 100), gridSizeX(gridSizeX), gridSizeY(gridSizeY), bombCount(bombCount)
{
    sf::Vector2u newWindowSize(gridSizeX * tileSize, gridSizeY * tileSize + 100);
    m_context->m_window->setSize(newWindowSize);
    sf::View newView(sf::FloatRect(0.f, 0.f, newWindowSize.x, newWindowSize.y));
    m_context->m_window->setView(newView);
}

void GamePlay::Init()
{
    TextureManager::loadTextures();

    int windowSizeX = m_context->m_window->getSize().x;
    int WindowSizeY = m_context->m_window->getSize().y;

    grid.initialize();
    grid.placeBombs(bombCount);
    grid.countBombsAround();

    if (!statsFont.loadFromFile("../assets/fonts/DayDream.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    // Initialize timer text
    timerText.setFont(statsFont);
    timerText.setString("000");
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::White);
    timerText.setStyle(sf::Text::Bold);

    timerText.setOrigin(timerText.getLocalBounds().width / 2, timerText.getLocalBounds().height / 2);
    timerText.setPosition(windowSizeX * 0.75, 50);

    remainingFlags = bombCount;
    flagCounterText.setFont(statsFont);
    flagCounterText.setString("000");
    flagCounterText.setCharacterSize(30);
    flagCounterText.setFillColor(sf::Color::White);
    flagCounterText.setStyle(sf::Text::Bold);

    flagCounterText.setOrigin(flagCounterText.getLocalBounds().width / 2, flagCounterText.getLocalBounds().height / 2);
    flagCounterText.setPosition(windowSizeX * 0.25, 50);
}

void GamePlay::setUpEndGameText(const string& message)
{
    int windowSizeX = m_context->m_window->getSize().x;
    int windowSizeY = m_context->m_window->getSize().y;

    endGameTextFont.setSmooth(true);
    if (!endGameTextFont.loadFromFile("../assets/fonts/DayDream.ttf"))
    {
        cerr << "Error loading font!" << std::endl;
        return;
    }

    endGameText.setFont(endGameTextFont);
    endGameText.setString(message);
    int baseFontSize = 50;
    int calculatedFontSize = std::min(windowSizeX, windowSizeY) / 10; // Proportional to window size
    endGameText.setCharacterSize(std::max(20, std::min(baseFontSize, calculatedFontSize))); // Clamp
    endGameText.setFillColor(sf::Color::Red);
    endGameText.setStyle(sf::Text::Bold);
    endGameText.setPosition(windowSizeX / 2, windowSizeY / 2);
    endGameText.setOrigin(endGameText.getLocalBounds().width / 2, endGameText.getLocalBounds().height / 1.5);
}

void GamePlay::checkGameState()
{
    if (gameOver && !startGameOverTimer)
    {
        startGameOverTimer = true; // Start the timer only once
        gameOverTimer.restart();

        if (!hasWon) // Player clicked on a bomb
        {
            setUpEndGameText("You Lose!");
        }
        else // All bombs are flagged correctly
        {
            setUpEndGameText("You Win!");
        }
    }
}


void GamePlay::ProcessInput()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_context->m_window);
    sf::Vector2i tileCoords = grid.getTileCoordinates(mousePos);

    if (!gameOver)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (!grid.revealTile(tileCoords.x, tileCoords.y))
            {
                cout << "Bomb!" << endl;
                gameOver = true;
                hasWon = false;
                grid.revealAllBombs();
            }
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            int flagged = grid.flagTile(tileCoords.x, tileCoords.y);
            cout << "flagged: " << flagged << endl;

            if (flagged == 1)
            {
                remainingFlags--;  // Decrease flag counter when a flag is placed
            }
            else if(flagged == 0)
            {
                remainingFlags++;  // Increase flag counter if a flag is removed
            }

            if (grid.areAllBombsFlagged())
            {
                gameOver = true;
                hasWon = true;
            }
        }
        checkGameState();
    }
}


void GamePlay::Update(const sf::Time& deltaTime)
{
    // Update the timer
    if (elapsedSeconds < 999 && !gameOver)
    {
        elapsedTime += deltaTime.asSeconds();
        if (elapsedTime >= 1.0f)
        {
            elapsedSeconds++;
            elapsedTime = 0.0f;

            std::ostringstream timerStream;
            timerStream << std::setw(3) << std::setfill('0') << elapsedSeconds;
            timerText.setString(timerStream.str());
        }
    }

    std::ostringstream flagStream;
    flagStream << std::setw(3) << std::setfill('0') << remainingFlags;
    flagCounterText.setString(flagStream.str());

    if (gameOver && startGameOverTimer)
    {
        if (gameOverTimer.getElapsedTime().asSeconds() >= 3.0f)
        {
            // Transition to the main menu state
            m_context->m_states->Add(std::make_unique<EndScreen>(m_context,hasWon, timerText.getString()), true);
        }
    }
}


void GamePlay::Draw()
{
    m_context->m_window->clear(sf::Color(83, 90, 102));

    grid.draw(*m_context->m_window);

    m_context->m_window->draw(timerText);
    m_context->m_window->draw(flagCounterText);

    if (gameOver)
    {
        m_context->m_window->draw(endGameText);
    }

    m_context->m_window->display();
}









//void GamePlay::placeBombs()
//{
//    int bombsPlaced = 0;
//    srand(static_cast<unsigned>(time(nullptr)));
//
//    while (bombsPlaced < bombCount)
//    {
//        int x = rand() % gridSizeX;
//        int y = rand() % gridSizeY;
//
//        if (!grid[y][x].hasBomb())
//        {
//            grid[y][x].setBomb(true);
//            bombsPlaced++;
//        }
//    }
//}
//
//void GamePlay::countBombsAround()
//{
//    for (int y = 0; y < gridSizeY; ++y)
//    {
//        for (int x = 0; x < gridSizeX; ++x)
//        {
//            if (!grid[y][x].hasBomb())
//            {
//                int bombsAround = 0;
//
//                // Check all adjacent tiles
//                for (int dy = -1; dy <= 1; ++dy)
//                {
//                    for (int dx = -1; dx <= 1; ++dx)
//                    {
//                        int nx = x + dx;
//                        int ny = y + dy;
//
//                        if (nx >= 0 && nx < gridSizeX && ny >= 0 && ny < gridSizeY && grid[ny][nx].hasBomb())
//                        {
//                            bombsAround++;
//                        }
//                    }
//                }
//
//                grid[y][x].setBombsAround(bombsAround);
//            }
//        }
//    }
//}
//
//void GamePlay::revealTile(int x, int y)
//{
//
//    // Base case: Out of bounds
//    if (x < 0 || x >= gridSizeX || y < 0 || y >= gridSizeY)
//        return;
//
//    // Base case: Already revealed
//    if (grid[y][x].getRevealedStatus())
//    {
//        cout << "Tile is already revealed (" << x << ", " << y << ")" << endl;
//        return;
//    }
//
//    // Base case: Stop if the tile contains a bomb
//    if (grid[y][x].hasBomb())
//    {
//        cout << "Tile has a bomb! (" << x << ", " << y << ")" << endl;
//        return;
//    }
//
//    // Reveal the current tile
//    if (grid[y][x].reveal())
//    {
//        cout << "Bombs around!" << endl;
//        return;
//    }
//    cout << "Revealing tile (" << x << ", " << y << ")" << endl;
//
//    // Otherwise, recursively reveal adjacent tiles
//    for (int dy = -1; dy <= 1; ++dy)
//    {
//        for (int dx = -1; dx <= 1; ++dx)
//        {
//            if (dx != 0 || dy != 0) // Skip the current tile
//            {
//                revealTile(x + dx, y + dy);
//            }
//        }
//    }
//}
//
//bool GamePlay::areAllBombsFlagged()
//{
//    for (int y = 0; y < gridSizeY; ++y)
//    {
//        for (int x = 0; x < gridSizeX; ++x)
//        {
//            if (grid[y][x].hasBomb() && !grid[y][x].getFlaggedStatus())
//            {
//                return false; // A bomb is not flagged
//            }
//        }
//    }
//
//    return true; // All bombs are flagged
//}




//void GamePlay::ProcessInput()
//{
//    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_context->m_window);
//
//    int x = mousePos.x / tileSize;
//    int y = mousePos.y / tileSize;
//
//    cout << x << endl;
//    cout << y << endl;
//
//    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//    {
//        if (x >= 0 && x < gridSizeX && y >= 0 && y < gridSizeY)
//        {
//            if (grid[y][x].hasBomb())
//            {
//                gameOver = true;
//                hasWon = false;
//            }
//            else
//            {
//                //grid[y][x].reveal();
//                revealTile(x, y);
//            }
//        }
//    }
//
//    //sf::Event event;
//    //while (m_context->m_window->pollEvent(event))
//    //{
//    //    if (event.type == sf::Event::Closed)
//    //    {
//    //        m_context->m_window->close();
//    //    }
//
//    //    if (!gameOver)
//    //    {
//    //        if (event.type == sf::Event::MouseButtonPressed)
//    //        {
//    //            sf::Vector2i mousePos = sf::Mouse::getPosition(*m_context->m_window);
//    //            int x = mousePos.x / tileSize;
//    //            int y = mousePos.y / tileSize;
//
//    //            if (x >= 0 && x < gridSizeX && y >= 0 && y < gridSizeY)
//    //            {
//    //                if (event.mouseButton.button == sf::Mouse::Left)
//    //                {
//    //                    if (grid[y][x].hasBomb())
//    //                    {
//    //                        gameOver = true;
//    //                        hasWon = false;
//    //                    }
//    //                    else
//    //                    {
//    //                        revealTile(x, y);
//    //                    }
//    //                }
//    //                else if (event.mouseButton.button == sf::Mouse::Right)
//    //                {
//    //                    // Toggle flag logic
//    //                    // Add a method in Tile for toggling flag and update it here
//    //                }
//    //            }
//    //        }
//    //    }
//    //}
//}




















//#include "GamePlay.h"
//#include "Tile.h"
//#include <iostream>
//
//using namespace std;
//
//GamePlay::GamePlay(shared_ptr<Context>& context) : m_context(context)
//{
//    cout << gridSizeX * tileSize << endl;
//    cout << gridSizeY * tileSize << endl;
//    TextureManager::loadTextures();
//    initializeGrid();
//    placeBombs();
//    countBombsAround();
//}
//
//void GamePlay::Init()
//{
//
//}
//
//void GamePlay::ProcessInput()
//{
//    sf::Event event;
//    while (m_context->m_window->pollEvent(event))
//    {
//        if (event.type == sf::Event::Closed)
//        {
//            m_context->m_window->close();
//        }
//
//        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//        {
//            sf::Vector2i mousePos = sf::Mouse::getPosition(*m_context->m_window);
//            int gridX = mousePos.x / tileSize;
//            int gridY = mousePos.y / tileSize;
//
//            if (gridX >= 0 && gridX < gridSizeX && gridY >= 0 && gridY < gridSizeY)
//            {
//                if (grid[gridY][gridX].hasBomb())
//                {
//                    setUpEndGameText("Game Over");
//                    m_context->m_window->close();
//                    cout << gridX << endl;
//                    cout << gridY << endl;
//                }
//                else
//                {
//                    /*grid[gridY][gridX].baseLayer.setTexture(TextureManager::getTexture("tileEmpty"));*/
//                    cout << gridX << endl;
//                    cout << gridY << endl;
//                }
//            }
//        }
//    }
//}
//
//void GamePlay::Update(const sf::Time& deltaTime)
//{
//
//}
//
//void GamePlay::Draw()
//{
//    m_context->m_window->clear(sf::Color::Black);
//
//    for (int y = 0; y < gridSizeY; ++y)
//    {
//        for (int x = 0; x < gridSizeX; ++x)
//        {
//            grid[y][x].draw(*m_context->m_window);
//        }
//    }
//
//    m_context->m_window->display();
//}
//
//
//
//
//void GamePlay::initializeGrid()
//{
//    grid.resize(gridSizeY, std::vector<Tile>(gridSizeX));
//    for (int y = 0; y < gridSizeY; ++y)
//    {
//        for (int x = 0; x < gridSizeX; ++x)
//        {
//            grid[y][x].initialize(x * tileSize, y * tileSize);
//        }
//    }
//}
//
//void GamePlay::placeBombs()
//{
//    int bombsPlaced = 0;
//    srand(static_cast<unsigned>(time(nullptr)));
//
//    while (bombsPlaced < bombCount)
//    {
//        int x = rand() % gridSizeX;
//        int y = rand() % gridSizeY;
//
//        if (!grid[y][x].hasBomb())
//        {
//            cout << "Bomb placed at ( " << x << ", " << y << " )" << endl;
//            grid[y][x].setBomb(true);
//            bombsPlaced++;
//        }
//    }
//}
//
//void GamePlay::countBombsAround()
//{
//    for (int y = 0; y < gridSizeY; ++y)
//    {
//        for (int x = 0; x < gridSizeX; ++x)
//        {
//            if (!grid[y][x].hasBomb())
//            {
//                int count = 0;
//                for (int dy = -1; dy <= 1; ++dy)
//                {
//                    for (int dx = -1; dx <= 1; ++dx)
//                    {
//                        int nx = x + dx, ny = y + dy;
//                        if (nx >= 0 && nx < gridSizeX && ny >= 0 && ny < gridSizeY && grid[ny][nx].hasBomb())
//                        {
//                            count++;
//                        }
//                    }
//                }
//                grid[y][x].setBombsAround(count);
//            }
//        }
//    }
//}
//
//void GamePlay::render()
//{
//    //window.clear();
//    for (int y = 0; y < gridSizeY; ++y)
//    {
//        for (int x = 0; x < gridSizeX; ++x)
//        {
//            grid[y][x].draw(window);
//        }
//    }
//    //window.display();
//}
//
//void GamePlay::setUpEndGameText(const std::string& message)
//{
//    sf::Font font;
//    if (!font.loadFromFile("../assets/fonts/DayDream.ttf"))
//    {
//        std::cerr << "Error loading font!" << std::endl;
//        return;
//    }
//    sf::Text text(message, font, 50);
//    endGameText.setFillColor(sf::Color::Red);
//    endGameText.setPosition((gridSizeX * tileSize) / 2 - 100, (gridSizeY * tileSize) / 2 - 25);
//    window.draw(text);
//    window.display();
//    sf::sleep(sf::seconds(3));
//}