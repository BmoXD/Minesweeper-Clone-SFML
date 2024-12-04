#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Tile
{
public:
    Tile();

    void initialize(float x, float y);
    void draw(sf::RenderWindow& window) const; 
    bool hasBomb() const { return isBomb; }
    void setBomb(bool bomb) { isBomb = bomb; }
    void setBombsAround(int count) { bombsAround = count; }
    bool reveal();
    void revealBomb();
    int getBombsAround() const { return bombsAround; };
    bool getRevealedStatus() const { return isRevealed; };
    bool getFlaggedStatus() const { return isFlagged; };

    void flag();

private:
    sf::Sprite baseLayer;
    sf::Sprite overlayLayer;
    bool isBomb = false;
    int bombsAround = 0;
    bool isRevealed = false;
    bool isFlagged = false;

};
