/*!
*	\brief "Snake Game" - Game Class.\n
*	\details The class implements functionality for the game process, scores, and supervising.\n
*	\author Olha Sereda
*	\date 2022
*   \copyright Olha Sereda (olha.sereda@student.uj.edu.pl)
*/

#pragma once
#include <cmath>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "snake.hpp"

class Game : public sf::Drawable
{
public:
	/*!
	* Class Game constructor\n
	* sets default params:\n
	* lives=5\n
	* fontsize=20\n
	* score=0\n
	* @param sf::Vector2u - screen size of game field - in pixels
	* @param path to the ttf font file.
	* @param pointer to the Snake hero object;
	* @see <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Vector2.php">sf::Vector2u</A>
	*/
	Game(sf::Vector2u, std::string, Snake*);
	/*!
	Virtual redefined function to draw full game area object on screen.\n
	It uses standart params to be used in sf::window.draw() method.
	@param target	Render target to draw to <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderTarget.php">sf::RenderTarget</A>
	@param states	Current render states <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderStates.php">sf::RenderStates</A>
	@see <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Drawable.php">sf::Drawable</A>
	*/
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	/*!
	* @param set Game::state of game: 0 - game; 1 - loose life; 2 - game over;
	*/
	void set_state(int);
	/*!
	* @return current Game::state of game: 0 - game; 1 - loose life; 2 - game over;
	*/
	int get_state(void);
	/*!
	* Method adds one to Game::score of game.
	*/
	void add_score(void);
	/*!
	* Method set Game::score to 0.
	*/
	void reset_score(void);
	/*!
	* Method decreace hero's lifes and in case of 0 change Game::state to 2 (game over).
	*/
	void hero_died(void);
	/*!
	* Method resets game attributes to default value.
	*/
	void reset_game(void);
	/*!
	* Metod changes Game::state to 0.
	*/
	void continue_game(void);
private:
	sf::Vector2u screensize;	///< game area(window) size
	int state;					///< state of game: 0 - game; 1 - loose life; 2 - game over;
	sf::Font font;				///< loaded font object
	int fontsize;				///< Size of the font in the game
	Snake *snake;				///< pointer to the Hero object
	int score;					///< score of the game - count of eated apples
	int life;					///< current count of Hero's lifes
};

