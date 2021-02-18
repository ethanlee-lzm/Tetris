#include "src/GameEngine/hpp/Components.hpp"
#include "src/DEFINE.hpp"
#include <iostream>

namespace hgw
{
	namespace cmp
	{
		VolumeBar::VolumeBar()
		{
			
		}

		void VolumeBar::Init(GameDataRef data)
		{
			this->_data = data;
			_data->graphics.LoadTexture("bar", VOLUME_BAR_FILEPATH);
			_data->graphics.LoadTexture("point", VOLUME_POINT_FILEPATH);

			_bar.setTexture(this->_data->graphics.GetTexture("bar"));
			_point.setTexture(this->_data->graphics.GetTexture("point"));

			_point.setOrigin(this->_point.getGlobalBounds().width / 2, this->_point.getGlobalBounds().height / 2);
		}

		void VolumeBar::Attach(sf::Sprite sprite, sf::Vector2f posDifference, float volume)
		{
			this->_bar.setPosition(sprite.getPosition().x - (_bar.getGlobalBounds().width - sprite.getGlobalBounds().width) / 2, 
				sprite.getPosition().y - posDifference.y);
			this->_point.setPosition(volume / 100 * this->_bar.getGlobalBounds().width + this->_bar.getPosition().x,
				sprite.getPosition().y - posDifference.y + this->_point.getGlobalBounds().height / 2);
		}

		void VolumeBar::MovePoint()
		{
			sf::Vector2f pointPos(to_float(sf::Mouse::getPosition(this->_data->window).x) , _point.getPosition().y);

			if (sf::Mouse::getPosition(this->_data->window).x > _bar.getPosition().x + _bar.getGlobalBounds().width)
			{
				pointPos.x = _bar.getPosition().x + _bar.getGlobalBounds().width;
			}
			else if (sf::Mouse::getPosition(this->_data->window).x < _bar.getPosition().x)
			{
				pointPos.x = _bar.getPosition().x;
			}

			this->_point.setPosition(pointPos);
		}

		float VolumeBar::GetVolume()
		{
			float barSize = this->_bar.getGlobalBounds().width;
			float barpoint = this->_bar.getPosition().x;
			float pointPos = sf::Mouse::getPosition(this->_data->window).x - barpoint;

			float volume = std::round(pointPos) / barSize * 100;

			if (volume > 100)
			{
				return 100;
			}
			else if (volume > 0)
			{
				return volume;
			}
			else
			{
				return 0;
			}
		}

	}
}