#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"

class Grid
{
public:
    Grid(int gridSizeX, int gridSizeY, int tileSize, int heightOffset);

    void initialize();
    void placeBombs(int bombCount);
    void countBombsAround();
    bool revealTile(int x, int y);
    int flagTile(int x, int y);
    void revealAllBombs();

    sf::Vector2i getTileCoordinates(const sf::Vector2i& mousePosition) const;
    void draw(sf::RenderWindow& window) const;

    bool areAllBombsFlagged() const;

private:
    int gridSizeX;
    int gridSizeY;
    const int tileSize = 32;
    const int heightOffset;
    std::vector<std::vector<Tile>> tiles;
};
