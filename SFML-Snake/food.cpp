/*!
*	\author Olha Sereda
*	\date 2022
*   \copyright Olha Sereda (olha.sereda@student.uj.edu.pl)
*/
#include "food.hpp"
#include "beer.hpp"

Food::Food(sf::Vector2f coord)
{
	this->coord=coord;

}

void Food::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	// draw green circle - like an apple :)
	sf::CircleShape cir;
	cir.setRadius(5);
	cir.setOutlineColor(sf::Color::Green);
	cir.setOutlineThickness(2);
	cir.setPosition(this->coord);
	cir.setOrigin(5,5);
	target.draw(cir, states);
}

sf::Vector2f Food::get_coord(void){
	return this->coord;
}


