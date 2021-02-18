#include "src\States\hpp\GameOverState.hpp"
#include "src\States\hpp\GameState.hpp"
#include "src\States\hpp\MenuState.hpp"
#include "src\States\hpp\SettingsState.hpp"
#include "src\DEFINE.hpp"

namespace hgw
{
	GameOverState::GameOverState(GameDataRef _data, bool multiplayerMatch)
	{
		this->_data = _data;
		this->multiplayerMatch = multiplayerMatch;
	}

	void GameOverState::Init()
	{
		_data->music.Play("gameOver");

		_data->graphics.LoadFont("font", FONT_PATH);

		gameOverText.setFont(_data->graphics.GetFont("font"));
		restartText.setFont(_data->graphics.GetFont("font"));
		mainMenuText.setFont(_data->graphics.GetFont("font"));
		exitText.setFont(_data->graphics.GetFont("font"));

		gameOverText.setString("GAME OVER");
		gameOverText.setCharacterSize(160);

		restartText.setString("START OVER");
		restartText.setCharacterSize(100);

		mainMenuText.setString("MAIN MENU");
		mainMenuText.setCharacterSize(100);

		exitText.setString("EXIT");
		exitText.setCharacterSize(100);

		gameOverText.setPosition((APP_WIDTH - gameOverText.getGlobalBounds().width) / 2 - 15,
								 (APP_HEIGHT - gameOverText.getGlobalBounds().height) / 10);

		restartText.setPosition((APP_WIDTH - restartText.getGlobalBounds().width) / 2, gameOverText.getPosition().y + 250);
		mainMenuText.setPosition((APP_WIDTH - mainMenuText.getGlobalBounds().width) / 2, restartText.getPosition().y + 100);
		exitText.setPosition((APP_WIDTH - exitText.getGlobalBounds().width) / 2, mainMenuText.getPosition().y + 100);
	}

	void GameOverState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}
			else if (_data->input.IsTextClicked(restartText, sf::Mouse::Left, event.type, _data->window))
			{
				_data->music.Stop("gameOver");
				_data->machine.AddState(StateRef(new GameState(_data)));
			}
			else if (_data->input.IsTextClicked(mainMenuText, sf::Mouse::Left, event.type, _data->window))
			{
				_data->music.Stop("gameOver");
				_data->machine.AddState(StateRef(new MenuState(_data)));
			}
			else if (_data->input.IsTextClicked(exitText, sf::Mouse::Left, event.type, _data->window))
			{
				_data->window.close();
			}
		}
	}

	void GameOverState::Update(float dt)
	{

	}

	void GameOverState::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(gameOverText);
		_data->window.draw(restartText);
		_data->window.draw(mainMenuText);
		_data->window.draw(exitText);

		_data->window.display();
	}
}