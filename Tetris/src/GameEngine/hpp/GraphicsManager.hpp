#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace hgw
{
	class GraphicsManager
	{
	public:
		GraphicsManager() {};
		~GraphicsManager() {};

		void LoadTexture(std::string name, std::string filename, bool setSmooth = true);
		sf::Texture &GetTexture(std::string name);

		void LoadFont(std::string name, std::string filename);
		sf::Font &GetFont(std::string name);

		void FadeIn(int changeValue, int endValue, sf::Sprite sprite);

	private:
		std::map<std::string, sf::Texture> _textures;
		std::map<std::string, sf::Font> _fonts;
	};
}
