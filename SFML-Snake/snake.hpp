/*!
*	\brief "Snake Game" - Snake Class.
*	\details The Class implements functionality for the snake hero object in game.\n
*	\author Olha Sereda
*	\date 2022
*   \copyright Olha Sereda (olha.sereda@student.uj.edu.pl)
*/

#pragma once
#include <cmath>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>


/*! \class Snake snake.hpp "snake.hpp"
 *	Class describes of Snake functionality and properties, as:\n 
 *  Changing direction, size of tail, checking of intersecton with itself.\n
 *	\n
 * Example:
 *  \code
 *		snake = new Snake(Vector2f(100,100),0,20);
 *		
 *		if (event.type == Event::KeyPressed)
 *		{
 *			if (event.key.code == Keyboard::Left) {
 *				snake->turn_left();
 *			}
 *			if (event.key.code == Keyboard::Right) {
 *				snake->turn_right();
 *			}
 *		}
 *		bool IsIntersected = sn->self_intersection();
 *		if (IsIntersected) DoSomethingToStopGame();
 *		snake->grow(10);
 *		delete(sn);
 *  \endcode
 */
class Snake : public sf::Drawable
{
public:
	/*!
	*	Class constructor\n
	*	Initiate attributes:\n
	*	Snake::delta=1\n
	*	Snake::speed=2\n
	*	Snake::color = sf::Color::Red;
	*	@param coords abcolute coordinate of Snake object location
	*	@param angle - initiate angle of direction on begin of movement
	*	@param size - initial size of snake after creation. Default size=20
	*	@see sf::Vector2f
	*/
	Snake(sf::Vector2f, float, int);
	/*!
	*	Virtual redefined function to draw Snake object on screen.\n
	*	It uses standart params to be used in sf::window.draw() method.
	*	@param target	Render target to draw to <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderTarget.php">sf::RenderTarget</A>
	*	@param states	Current render states <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderStates.php">sf::RenderStates</A>
	*	@see <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Drawable.php">sf::Drawable</A>
	*/
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	/*!
	*	Method updates all Snake params on the each Game tick.\n
	*   It adds new array element with new coords to the begin of array\n
	*   If the count of sections of Snake Hero in array greater or equal then size of Hero then remove one element from tail's end\n
	*   Inserting new element with new coords to head and removing one element from end makes movement effect\n
	*	Metod can be called only one times per game tick to avoid unpredicted movement or states.
	*/
	void update();
	/*!
	*	Method changes angle to counterclock-wise on Snake::delta value of movement Snake.\n
	*	On each continuous call of method the Snake::delta increace to +0.5 to make feeling of turning acceleration.\n
	*	Metod can be called only one times per game tick to avoid unpredicted movement or states.
	*/
	void turn_left();
	/*!
	*	Method changes angle to clockwise on Snake::delta value of movement Snake.\n
	*	On each continuous call of method the Snake::delta increace to +0.5 to make feeling of turning acceleration.\n
	*	Metod can be called only one times per game tick to avoid unpredicted movement or states.
	*/
	void turn_right();
	/*!
	* Enlarge tail to the number of elements.
	* @param count and new tail elements
	*/
	void grow(unsigned int);
	/*!
	* Set Snake::delta to 1;
	*/
	void reset_delta();
	/*!
	* @return Method returns the coordinates of the head of snake (first tail element).
	* @see <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Vector2.php">sf::Vector2f</A>
	*/
	sf::Vector2f get_coord(void);
	/*!
	* @return Method returns the set of box(rectangle) coordinates of head of snake (first tail element).
	* @see <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Rect.php">sf::FloatRect</A>
	*/	
	sf::FloatRect GetRect(void);
	/*!
	* @return Method returns true in case of head(first element) intersected with its tail.
	* @see <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Rect.php">sf::FloatRect</A>
	*/
	bool self_intersection(void);
	/*!
	* @return Method returns length of the tail.
	* @see <A HREF="https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Rect.php">sf::FloatRect</A>
	*/
	int get_size(void);
private:
	sf::Color color;	///< value current color of the snake object.
	float speed;		///< value of length of movoment on each game tick.
	float delta;		///< value of current delta of turning.
	float angle;		///< value of current ansolute angle of direction in degrees.
	int size;			///< value of current tail size.
	std::vector <sf::Vector2f> path;	///< array of the all tail elements.
	/*!
		Method measures geometric offset vector relative to angle of direction and step length.
		@param absolute angle of movement in degrees.
		@param offset lenght value.
		@return geometric offset vector.
	*/
	sf::Vector2f CalcDiff(float, float);

};
