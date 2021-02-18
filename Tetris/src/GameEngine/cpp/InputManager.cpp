#include "src/GameEngine/hpp/InputManager.hpp"
#include "src/DEFINE.hpp"

namespace hgw
{
	bool InputManager::IsSpriteHeld(sf::Sprite object,
		sf::Mouse::Button button, sf::RenderWindow &window)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			sf::FloatRect tempRect(object.getPosition().x, object.getPosition().y,
				object.getGlobalBounds().width, object.getGlobalBounds().height);

			if (tempRect.contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				return true;
			}
		}
		return false;
	}

	bool InputManager::IsIntRectHeld(sf::IntRect intRect,
		sf::Mouse::Button button, sf::RenderWindow &window)
	{
		if (sf::Mouse::isButtonPressed(button) &&
			intRect.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
		return false;
	}

	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button,
		sf::Event::EventType eventType, sf::RenderWindow &window)
	{
		if (eventType == sf::Event::EventType::MouseButtonPressed)
		{
			sf::FloatRect tempRect(object.getPosition().x, object.getPosition().y, 
				object.getGlobalBounds().width,	object.getGlobalBounds().height);

			if (sf::Mouse::isButtonPressed(button) && 
				tempRect.contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				return true;
			}
		}
		return false;
	}

	bool InputManager::IsIntRectClicked(sf::IntRect intRect, sf::Mouse::Button button,
		sf::Event::EventType eventType, sf::RenderWindow &window)
	{
		if (eventType == sf::Event::EventType::MouseButtonPressed &&
			sf::Mouse::isButtonPressed(button) &&
			intRect.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
		return false;
	}

	bool InputManager::IsSpriteReleased(sf::Sprite object, sf::Mouse::Button button,
		sf::Event::EventType eventType, sf::RenderWindow &window)
	{
		if (eventType == sf::Event::EventType::MouseButtonReleased)
		{
			sf::FloatRect tempRect(object.getPosition().x, object.getPosition().y,
				object.getGlobalBounds().width, object.getGlobalBounds().height);

			if (tempRect.contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				return true;
			}
		}
		return false;
	}

	bool InputManager::IsTextClicked(sf::Text text, sf::Mouse::Button button, sf::Event::EventType eventType, sf::RenderWindow &window, sf::Vector2i scale)
	{
		if (eventType == sf::Event::EventType::MouseButtonPressed)
		{
			sf::FloatRect tempRect;
			tempRect.height = text.getGlobalBounds().height + 5;
			tempRect.width = text.getGlobalBounds().width;
			tempRect.top = text.getPosition().y + text.getGlobalBounds().height / 2;
			tempRect.left = text.getPosition().x + 5;
			
			tempRect = scaleFloatRect(tempRect, scale); //it just works

			if (sf::Mouse::isButtonPressed(button) &&
				tempRect.contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				return true;
			}
		}
		return false;
	}

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window)
	{
		return sf::Mouse::getPosition(window);
	}

	sf::FloatRect InputManager::scaleFloatRect(sf::FloatRect fr, sf::Vector2i scale)
	{
		fr = translateFloatRect(fr ,sf::Vector2i(-fr.width * (scale.x - 1), -fr.height * (scale.y - 1))); //shit needed to adjust text floatRect, may redo later
		return sf::FloatRect{ fr.left, fr.top, fr.width * scale.x, fr.height * scale.y };
	}

	sf::FloatRect InputManager::translateFloatRect(sf::FloatRect fr, sf::Vector2i translate) //^
	{
		return sf::FloatRect{ fr.left + translate.x, fr.top + translate.y, fr.width, fr.height};
	}
}