#include "TextureManager.h"
#include <iostream>

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::loadTextures() {
    vector<pair<string, string>> files =
    {
        {"button", "../assets/button.png"},
        {"tileCovered", "../assets/tiles/tileCovered.png"},
        {"tileEmpty", "../assets/tiles/tileEmpty.png"},
        {"mine", "../assets/tiles/mine.png"},
        {"flag", "../assets/tiles/flag.png"},
        {"1", "../assets/tiles/1.png"},
        {"2", "../assets/tiles/2.png"},
        {"3", "../assets/tiles/3.png"},
        {"4", "../assets/tiles/4.png"},
        {"5", "../assets/tiles/5.png"},
        {"6", "../assets/tiles/6.png"},
        {"7", "../assets/tiles/7.png"},
        {"8", "../assets/tiles/8.png"}
    };

    for (const auto& [key, path] : files)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(path))
        {
            cerr << "Error: Failed to load texture from " << path << endl;
        }
        else
        {
            textures[key] = move(texture);
        }
    }
}

// Get a texture by name
const sf::Texture& TextureManager::getTexture(const string& name)
{
    return textures.at(name);
}
