#pragma once

#define APP_NAME "Tetris"

#define FONT_PATH "res/fonts/FreePixel.ttf"

#define APP_HEIGHT 900
#define APP_WIDTH 800

#define BLOCK_SIZE 30
#define ENEMY_BLOCK_SIZE 15

#define GRID_START_POS_X 250
#define GRID_START_POS_Y 100
#define GRID_END_POS_Y 700
#define GRID_END_POS_X 550

#define EMPTY_GRID_PLACE std::pair<bool, sf::RectangleShape>(false, sf::RectangleShape())
#define FILLED_GRID_PLACE std::pair<bool, sf::RectangleShape>(true, sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)))

#define VOLUME_BAR_FILEPATH "res/gfx/Volume Bar.png"
#define VOLUME_POINT_FILEPATH "res/gfx/Volume Point.png"

#define SOUND_OFF_FILEPATH "res/gfx/Sound Off.png"
#define SOUND_ON_FILEPATH "res/gfx/Sound On.png"

#define MUSIC_OFF_FILEPATH "res/gfx/Music Off.png"
#define MUSIC_ON_FILEPATH "res/gfx/Music On.png"

#define CLEAR1_SOUND_PATH "res/audio/sounds/clear1.wav"
#define CLEAR2_SOUND_PATH "res/audio/sounds/clear2.wav"
#define CLEAR3_SOUND_PATH "res/audio/sounds/clear3.wav"
#define CLEAR4_SOUND_PATH "res/audio/sounds/clear4.wav"

#define GAME_MUSIC_PATH "res/audio/music/gameMusic.wav"
#define MENU_MUSIC_PATH "res/audio/music/menuMusic.wav"
#define GAME_OVER_MUSIC_PATH "res/audio/music/gameOver.wav"

#define to_uns(x) static_cast<unsigned>(x)
#define to_float(x) static_cast<float>(x)
//#define to_type<class T, x> static_cast<T>(x)