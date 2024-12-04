#include "Tile.h"
#include <string>

using namespace std;

Tile::Tile() {}

void Tile::initialize(float x, float y)
{
    baseLayer.setTexture(TextureManager::getTexture("tileCovered"));
    baseLayer.setPosition(x, y);
    overlayLayer.setPosition(x, y);
}

bool Tile::reveal()
{
    if (!isFlagged)
    {
        sf::FloatRect tileGLobalBounds = baseLayer.getGlobalBounds();
        isRevealed = true;

        if (bombsAround > 0)
        {
            baseLayer.setTexture(TextureManager::getTexture(to_string(bombsAround)));
            return true;
        }
        else
        {
            baseLayer.setTexture(TextureManager::getTexture("tileEmpty"));
            return false;
        }
    }
}

void Tile::revealBomb()
{
    overlayLayer.setTexture(TextureManager::getTexture("mine"));
    overlayLayer.setColor(sf::Color(255, 255, 255, 255));
}

void Tile::flag()
{
    if (!isRevealed)
    {
        if (!isFlagged)
        {
            overlayLayer.setTexture(TextureManager::getTexture("flag"));
            overlayLayer.setColor(sf::Color(255, 255, 255, 255));
        }
        else
        {
            overlayLayer.setColor(sf::Color(255, 255, 255, 0));
        }
        isFlagged = !isFlagged;
    }
}

void Tile::draw(sf::RenderWindow& window) const
{
    window.draw(baseLayer);
    window.draw(overlayLayer);
}
