#pragma once

#include <map>

#include <SFML/Graphics.hpp>
// Manager for assets such as textures and fonts
namespace izombie
{
       class AssetManager
       {
       public:
            AssetManager() {}
            ~AssetManager() {}

            void LoadTexture(std::string name, std::string fileName);
            sf::Texture &GetTexture(std::string name);

            void LoadFont(std::string name, std::string fileNme);
            sf::Font &GetFont(std::string name);

       private:
           std::map<std::string, sf::Texture> textures;
           std::map<std::string, sf::Font> fonts;
       };
}