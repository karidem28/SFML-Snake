/*!
*	\brief "Snake Game" - GameMap Class.\n
*	\details The class implements functionality for the game levels structure.\n
*	\author Olha Sereda
*	\date 2022
*   \copyright Olha Sereda (olha.sereda@student.uj.edu.pl)
*/

#pragma once
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>


class GameMap : public sf:: Drawable
{
public:
	/*!
	* Class constructor\n
	* Creates blank level object.
	*/
	GameMap(void);
	/*!
	Virtual redefined function to draw game level object on screen.\n
	It uses standart params to be used in sf::window.draw() method.
	@param target	Render target to draw to <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderTarget.php">sf::RenderTarget</A>
	@param states	Current render states <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderStates.php">sf::RenderStates</A>
	@see <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Drawable.php">sf::Drawable</A>
	*/
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	/*!
	* @param rectangle coordinated incapsulated into <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Rect.php">sf::FloatRect</A> object.
	* @retrun true if the parameter's rectangle intersects with any of level wall.
	*/
	bool check_intersection_with_circle(sf::FloatRect);
	/*!
	* Adds new wall rectange to the array od walls in level.
	* @param rectangle coordinated incapsulated into <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Rect.php">sf::FloatRect</A> object.
	*/
	void add_wall(sf::FloatRect);
	/*!
	* Method clears array os level walls.
	*/
	void reset(void);
private:
	std::vector <sf::FloatRect> walls;	///< array of walls rectangle coordiantes incapsulated into <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Rect.php">sf::FloatRect</A> object..

};
