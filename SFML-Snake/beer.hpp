/*!
*	\brief "Snake Game" - Beer Class.\n
*	\details The Class implements functionality for the beer object in game.\n
*	\author Olha Sereda
*	\date 2022
*   \copyright Olha Sereda (olha.sereda@student.uj.edu.pl)
*/


#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>


/*! \class Beer beer.hpp "beer.hpp"
 *	Array of objects of Food class can be putten on the screen to \n
 *  make Snake not hungry.\n
 *  The main goal of game to eat Food as long as it possible and avoid all obstacles.\n
 *  \n
 * Example:
 *  \code
 *		fptr = new Food(Vector2f(f_coord.left,f_coord.top));
 *  \endcode
 */
class Beer : public sf::Drawable
{
public:
	/*!
	Class constructor
	@param sf::Vector2f - abcolute coordinate of food object location
	@see <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Vector2.php">sf::Vector2f</A>
	*/
	Beer(sf::Vector2f);
	/*!
	Virtual redefined function to draw Food object on screen.\n
	It uses standart params to be used in sf::window.draw() method.
	@param target	Render target to draw to <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderTarget.php">sf::RenderTarget</A>
	@param states	Current render states <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderStates.php">sf::RenderStates</A>
	@see <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Drawable.php">sf::Drawable</A>
	*/
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	/*!
	@return current absolute coodinates of food object location
	@see <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Vector2.php">sf::Vector2f</A>
	*/
	sf::Vector2f get_coord(void);
	sf::FloatRect get_rect(void);
	void Update();
	bool IsAlive();


private:
	sf::Vector2f coord; ///**< value of current coordinates. <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Vector2.php">sf::Vector2f</A> */ 
	int TimeOfLife;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
};
