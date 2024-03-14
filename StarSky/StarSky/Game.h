/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

enum class Direction
{
	None,
	Left,
	Right
};

const int HEIGHT = 800;
const int WIDTH = 1000;

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouse(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void setupSky();
	void animateStars();
	void starsMove();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	//sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_starsTexture; // texture used for sfml stars
	sf::Sprite m_stars; // sprite used for sfml logo
	sf::Texture m_skyTexture; //texture used for sfml sky
	sf::Sprite m_skySprite; //sprite used for sfml sky
	bool m_exitGame; // control exiting game

	int m_currentFrame = 0;
	float m_currentFrameCounter = 0.0f;
	float m_frameIncrement = 0.26f;

	sf::Vector2f m_starslocation{ 0.0f, 550.0f };
	sf::Vector2f m_velocity{ 1.0f, 1.0f };
	sf::Vector2f m_target{ 1.0f,1.0f };
	Direction m_facing = Direction::None;
	float m_speed = 4.0f; // speed in straight line

};

#endif // !GAME_HPP

