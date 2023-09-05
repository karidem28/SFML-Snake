
/*!
*	\author Olha Sereda
*	\date 2022
*   \copyright Olha Sereda (olha.sereda@student.uj.edu.pl)
*/
#include "beer.hpp"

Beer::Beer(sf::Vector2f coord)
{
	this->coord = coord;
	this->TimeOfLife = 100;
	image.loadFromFile("beer-icon.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setPosition(this->coord);
}

void Beer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	
	target.draw(sprite, states);
}

sf::Vector2f Beer::get_coord(void) {
	return this->coord;
	
}

sf::FloatRect Beer::get_rect(void)
{
	return sf::FloatRect(this->coord.x,this->coord.y,sprite.getTextureRect().width,sprite.getTextureRect().height);
}

void Beer::Update()
{
	TimeOfLife--;
}

bool Beer::IsAlive()
{
	if (TimeOfLife > 0)return true;
	else return false;
}

