#include "src/States/hpp/SettingsState.hpp"
#include "src/States/hpp/MenuState.hpp"
#include "src/States/hpp/GameState.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include "src/GameEngine/hpp/Components.hpp"
#include "src/DEFINE.hpp"
#include <iostream>

namespace hgw
{
	SettingsState::SettingsState(GameDataRef _data, bool additionalBackOption)
	{
		this->_data = _data;
		this->additionalBackOption = additionalBackOption;
	}

	void SettingsState::Init()
	{
		_data->graphics.LoadFont("font", FONT_PATH);

		if (additionalBackOption)
		{
			returnText.setFont(_data->graphics.GetFont("font"));
			additionalReturnText.setFont(_data->graphics.GetFont("font"));

			returnText.setCharacterSize(50);
			returnText.setString("Back to game");

			additionalReturnText.setCharacterSize(50);
			additionalReturnText.setString("Back to main menu");

			returnText.setPosition((APP_WIDTH - returnText.getGlobalBounds().width) / 2, 750);
			additionalReturnText.setPosition((APP_WIDTH - additionalReturnText.getGlobalBounds().width) / 2, returnText.getPosition().y + 50);
		}	
		else
		{
			returnText.setFont(_data->graphics.GetFont("font"));
			additionalReturnText.setFont(_data->graphics.GetFont("font"));

			returnText.setCharacterSize(50);
			returnText.setString("Back to main menu");

			returnText.setPosition((APP_WIDTH - returnText.getGlobalBounds().width) / 2, 775);
		}

		_data->graphics.LoadTexture("sound off", SOUND_OFF_FILEPATH);
		_data->graphics.LoadTexture("sound on", SOUND_ON_FILEPATH);
		_data->graphics.LoadTexture("music off", MUSIC_OFF_FILEPATH);
		_data->graphics.LoadTexture("music on", MUSIC_ON_FILEPATH);

		soundBar.Init(_data);
		musicBar.Init(_data);

		soundOff.setTexture(_data->graphics.GetTexture("sound off"));
		soundOn.setTexture(_data->graphics.GetTexture("sound on"));

		musicOff.setTexture(_data->graphics.GetTexture("music off"));
		musicOn.setTexture(_data->graphics.GetTexture("music on"));

		soundOff.setScale(0.7f, 0.7f);
		soundOn.setScale(0.7f, 0.7f);
		musicOff.setScale(0.7f, 0.7f);
		musicOn.setScale(0.7f, 0.7f);

		originalColorText.setFont(_data->graphics.GetFont("font"));
		originalColorText.setCharacterSize(50);
		if (_data->gameData.gameData.originalColors)
		{
			originalColorText.setString("Original Colors: ON");
		}
		else
		{
			originalColorText.setString("Original Colors: OFF");
		}

		drawFullGridText.setFont(_data->graphics.GetFont("font"));
		drawFullGridText.setCharacterSize(50);
		if (_data->gameData.gameData.fullGrid)
		{
			drawFullGridText.setString("Draw Full Grid: ON");
		}
		else
		{
			drawFullGridText.setString("Draw Full Grid: OFF");
		}
			
		originalColorText.setPosition((APP_WIDTH - originalColorText.getGlobalBounds().width) / 2, 180);
		drawFullGridText.setPosition((APP_WIDTH - drawFullGridText.getGlobalBounds().width) / 2, 230);

		soundOff.setPosition((APP_WIDTH - soundOff.getGlobalBounds().width) / 5 + 70, 50);
		soundOn.setPosition((APP_WIDTH - soundOn.getGlobalBounds().width) / 5 + 70, 50);
		
		musicOff.setPosition(soundOff.getPosition().x + drawFullGridText.getGlobalBounds().width - 170, 50);
		musicOn.setPosition(soundOff.getPosition().x + drawFullGridText.getGlobalBounds().width - 170, 50);

		musicBar.Attach(musicOff, sf::Vector2f(0, -musicOn.getGlobalBounds().height - 10), _data->music.getGlobalVolume());
		soundBar.Attach(soundOff, sf::Vector2f(0, -soundOn.getGlobalBounds().height - 10), _data->sounds.getGlobalVolume());
	}

	void SettingsState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}
			else if (_data->input.IsTextClicked(returnText, sf::Mouse::Left, event.type, _data->window))
			{
				_data->machine.RemoveState();
			}
			else if (_data->input.IsTextClicked(additionalReturnText, sf::Mouse::Left, event.type, _data->window))
			{
				if (additionalBackOption)
				{
					_data->machine.RemoveState();
					_data->machine.AddState(StateRef(new MenuState(_data)));
				}
			}
			else if (_data->input.IsTextClicked(drawFullGridText, sf::Mouse::Left, event.type, _data->window))
			{
				_data->gameData.gameData.fullGrid = !_data->gameData.gameData.fullGrid;
				_data->gameData.serializeSave();

				if (_data->gameData.gameData.fullGrid)
				{
					drawFullGridText.setString("Draw Full Grid: ON");
				}
				else
				{
					drawFullGridText.setString("Draw Full Grid: OFF");
				}		
			}
			else if (_data->input.IsTextClicked(originalColorText, sf::Mouse::Left, event.type, _data->window))
			{
				_data->gameData.gameData.originalColors = !_data->gameData.gameData.originalColors;
				_data->gameData.serializeSave();

				if (_data->gameData.gameData.originalColors)
				{
					originalColorText.setString("Original Colors: ON");
				}
				else
				{
					originalColorText.setString("Original Colors: OFF");
				}			
			}
			else if (sf::Event::MouseButtonReleased == event.type && event.mouseButton.button == sf::Mouse::Left)
			{
				soundPointPressed = false;
				musicPointPressed = false;

				std::cout << "SOUND BAR RELEASED" << std::endl;
			}
			else if (_data->input.IsSpriteClicked(soundBar._bar, sf::Mouse::Left, event.type, _data->window))
			{
				soundPointPressed = true;
			}
			else if (_data->input.IsSpriteClicked(musicBar._bar, sf::Mouse::Left, event.type, _data->window))
			{
				musicPointPressed = true;
			}
		}
	}

	void SettingsState::Update(float dt)
	{
		if (soundPointPressed)
		{
			soundBar.MovePoint();
			_data->sounds.setGlobalVolume(soundBar.GetVolume());
			_data->gameData.gameData.soundVolume = soundBar.GetVolume();
			_data->gameData.serializeSave();
			_data->sounds.setAllSoundsToGlobalVolume();
		}
		else if (musicPointPressed)
		{
			musicBar.MovePoint();
			_data->music.setGlobalVolume(musicBar.GetVolume());
			_data->gameData.gameData.musicVolume = musicBar.GetVolume();
			_data->gameData.serializeSave();
			_data->music.setAllSongsToGlobalVolume();
		}
		std::cout << "SOUND: " << _data->sounds.getGlobalVolume() << std::endl;
		std::cout << "MUSIC: " << _data->music.getGlobalVolume() << std::endl;
	}

	void SettingsState::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(originalColorText);
		_data->window.draw(drawFullGridText);
		_data->window.draw(returnText);

		if (additionalBackOption)
		{	
			_data->window.draw(additionalReturnText);
		}

		if (_data->sounds.getGlobalVolume() <= 0)
		{
			_data->window.draw(soundOff);
		}
		else
		{
			_data->window.draw(soundOn);
		}

		if (_data->music.getGlobalVolume() <= 0)
		{
			_data->window.draw(musicOff);
		}
		else
		{
			_data->window.draw(musicOn);
		}

		_data->window.draw(musicBar._bar);
		_data->window.draw(musicBar._point);
		_data->window.draw(soundBar._bar);
		_data->window.draw(soundBar._point);

		_data->window.display();
	}
}