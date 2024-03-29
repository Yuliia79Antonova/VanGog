/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMouse(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::processMouse(sf::Event t_event)
{
	float lenght = 0.0f;
	sf::Vector2f displacement(0.0f, 0.0f);
	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		displacement.x = static_cast<float>(t_event.mouseButton.x) - m_starslocation.x;
		displacement.y = static_cast<float>(t_event.mouseButton.y) - m_starslocation.y;
		m_target.x = t_event.mouseButton.x;
		m_target.y = t_event.mouseButton.y;
		lenght = std::sqrt((displacement.x * displacement.x) + (displacement.y * displacement.y));
		displacement = displacement / lenght;
		displacement = displacement * m_speed;
		m_velocity = displacement;
	}
	if (static_cast<float>(t_event.mouseButton.x) > m_starslocation.x)
		{
			m_facing = Direction::Right;
			m_stars.setScale(1.0, 1.0);
		}
	else
		{
			m_facing = Direction::Left;
			m_stars.setScale(-1.0, 1.0);
		}
}


/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	starsMove();
	animateStars();
	
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_skySprite);
	//m_window.draw(m_welcomeMessage);
	m_window.draw(m_stars);
	m_window.display();
	
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	/*m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);*/

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_starsTexture.loadFromFile("ASSETS\\IMAGES\\stars.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading stars" << std::endl;
	}
	m_stars.setTexture(m_starsTexture);
	m_stars.setTextureRect(sf::IntRect(0, 0, 200,64));
	m_stars.setPosition(m_starslocation);
	m_stars.setOrigin(90.0f, 32.0f);
	setupSky();
}

void Game::setupSky()
{
	if (!m_skyTexture.loadFromFile("ASSETS\\IMAGES\\starSky.jpg"))
	{
		std::cout << "problem with sky" << std::endl;
	}
	m_skyTexture.setRepeated(true);
	m_skySprite.setTexture(m_skyTexture);
	m_skySprite.setTextureRect(sf::IntRect{ 0,0,WIDTH,HEIGHT });
}

void Game::animateStars()
{
	int newFrameNumber = 0;
	m_currentFrameCounter += m_frameIncrement;
	newFrameNumber = static_cast<int>(m_currentFrameCounter);
	newFrameNumber = newFrameNumber % 4; 
	if (newFrameNumber != m_currentFrame)
	{
		m_currentFrame = newFrameNumber;
		m_stars.setTextureRect(sf::IntRect(0, 64, 180, 180));
	}
}

void Game::starsMove()
{
	if (m_facing != Direction::None)
	{
		m_starslocation += m_velocity;
		m_stars.setPosition(m_starslocation);


		if (m_facing == Direction::Right && m_starslocation.x > m_target.x)
		{
			m_facing = Direction::None;
		}
		if (m_facing == Direction::Left && m_starslocation.x < m_target.x)
		{
			m_facing = Direction::None;
		}
	}
}
