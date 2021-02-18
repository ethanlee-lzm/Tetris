#pragma once

#include <SFML/Graphics.hpp>

namespace hgw
{
	class InputManager
	{
	public:
		InputManager() {}
		~InputManager() {}

		bool IsSpriteHeld(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
		bool IsIntRectHeld(sf::IntRect intRect, sf::Mouse::Button button, sf::RenderWindow &window);

		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::Event::EventType eventType, sf::RenderWindow &window);
		bool IsIntRectClicked(sf::IntRect intRect, sf::Mouse::Button button, sf::Event::EventType eventType, sf::RenderWindow &window);

		bool IsSpriteReleased(sf::Sprite object, sf::Mouse::Button button, sf::Event::EventType eventType, sf::RenderWindow &window);

		bool IsTextClicked(sf::Text text, sf::Mouse::Button button, sf::Event::EventType eventType, sf::RenderWindow &window, sf::Vector2i scale = sf::Vector2i(1,1));

		sf::Vector2i GetMousePosition(sf::RenderWindow &window);
	private:
		sf::FloatRect scaleFloatRect(sf::FloatRect fr, sf::Vector2i scale);
		sf::FloatRect translateFloatRect(sf::FloatRect fr, sf::Vector2i translate);
	};
}