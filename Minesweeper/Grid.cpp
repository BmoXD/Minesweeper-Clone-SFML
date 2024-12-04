#include "Grid.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Grid::Grid(int gridSizeX, int gridSizeY, int tileSize, int heightOffset)
    : gridSizeX(gridSizeX), gridSizeY(gridSizeY), tileSize(tileSize), heightOffset(heightOffset)
{
    tiles.resize(gridSizeY, std::vector<Tile>(gridSizeX));
}

void Grid::initialize()
{
    for (int y = 0; y < gridSizeY; ++y)
    {
        for (int x = 0; x < gridSizeX; ++x)
        {
            tiles[y][x].initialize(x * tileSize, y * tileSize + heightOffset);
        }
    }
}

void Grid::placeBombs(int bombCount)
{
    int bombsPlaced = 0;
    srand(static_cast<unsigned>(time(nullptr)));

    while (bombsPlaced < bombCount)
    {
        int x = rand() % gridSizeX;
        int y = rand() % gridSizeY;

        if (!tiles[y][x].hasBomb())
        {
            tiles[y][x].setBomb(true);
            bombsPlaced++;
        }
    }
}

void Grid::countBombsAround()
{
    for (int y = 0; y < gridSizeY; ++y)
    {
        for (int x = 0; x < gridSizeX; ++x)
        {
            if (!tiles[y][x].hasBomb())
            {
                int bombsAround = 0;

                for (int dy = -1; dy <= 1; ++dy)
                {
                    for (int dx = -1; dx <= 1; ++dx)
                    {
                        int nx = x + dx;
                        int ny = y + dy;

                        if (nx >= 0 && nx < gridSizeX && ny >= 0 && ny < gridSizeY && tiles[ny][nx].hasBomb())
                        {
                            bombsAround++;
                        }
                    }
                }
                tiles[y][x].setBombsAround(bombsAround);
            }
        }
    }
}

bool Grid::revealTile(int x, int y)
{
    if (x < 0 || x >= gridSizeX || y < 0 || y >= gridSizeY || tiles[y][x].getRevealedStatus() || tiles[y][x].getFlaggedStatus())
        return true;

    if (tiles[y][x].hasBomb())
    {
        return false;
    }

    if (tiles[y][x].reveal())
        return true;

    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            if (dx != 0 || dy != 0)
            {
                revealTile(x + dx, y + dy);
            }
        }
    }
}

int Grid::flagTile(int x, int y)
{
    cout << x << ", " << y << endl;
    if (x >= 0 && x < gridSizeX && y >= 0 && y < gridSizeY)
    {
        tiles[y][x].flag();
        if (!tiles[y][x].getRevealedStatus() && tiles[y][x].getFlaggedStatus())
        {
            return 1;
        }
        if (!tiles[y][x].getRevealedStatus() && !tiles[y][x].getFlaggedStatus())
        {
            return 0;
        }
    }
    cout << "adadsad" << endl;
    return -1;
}

sf::Vector2i Grid::getTileCoordinates(const sf::Vector2i& mousePosition) const
{
    int adjustedY = mousePosition.y - heightOffset;
    if (adjustedY < 0) return sf::Vector2i(-1, -1); // Out of bounds above the grid
    return sf::Vector2i(mousePosition.x / tileSize, adjustedY / tileSize);
}

void Grid::draw(sf::RenderWindow& window) const
{
    for (int y = 0; y < gridSizeY; ++y)
    {
        for (int x = 0; x < gridSizeX; ++x)
        {
            tiles[y][x].draw(window);
        }
    }
}

bool Grid::areAllBombsFlagged() const
{
    for (int y = 0; y < gridSizeY; ++y)
    {
        for (int x = 0; x < gridSizeX; ++x)
        {
            // Check if there is tile that has a bomb and if it's flagged
            if (tiles[y][x].hasBomb() && !tiles[y][x].getFlaggedStatus())
                return false;

            // Check if there is a tile that doesn't have a bomb and if it's flagged
            if (!tiles[y][x].hasBomb() && tiles[y][x].getFlaggedStatus())
                return false;
        }
    }
    return true;
}

void Grid::revealAllBombs()
{
    for (int y = 0; y < gridSizeY; ++y)
    {
        for (int x = 0; x < gridSizeX; ++x)
        {
            if (tiles[y][x].hasBomb())
            {
                tiles[y][x].revealBomb();
            }
        }
    }
}
