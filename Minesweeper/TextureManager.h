#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

using namespace std;

class TextureManager
{
    public:
        // Load all textures
        static void loadTextures();

        // Get a texture by name
        static const sf::Texture& getTexture(const std::string& name);

    private:
        // Storage for textures
        static unordered_map<string, sf::Texture> textures;
};
