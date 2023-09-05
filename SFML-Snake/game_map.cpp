/*!
*	\author Olha Sereda
*	\date 2022
*   \copyright Olha Sereda (olha.sereda@student.uj.edu.pl)
*/
#include "game_map.hpp"

GameMap::GameMap(void){
	this->walls.clear();
}

void GameMap::draw(sf::RenderTarget& rt, sf::RenderStates st) const{

	sf::RectangleShape rect;
	// draw all walls from the array of box(Rect) coordinates
	for(auto it=this->walls.begin(); it!=this->walls.end(); it=next(it))
	{
		rect.setSize(sf::Vector2f((*it).width,(*it).height));
		rect.setPosition(sf::Vector2f((*it).left,(*it).top));
		//rect.setOutlineColor(sf::Color::Yellow);
		rect.setFillColor(sf::Color::Yellow);
		//rect.setOutlineThickness(3);
		rt.draw(rect,st);
	}

}

bool GameMap::check_intersection_with_circle(sf::FloatRect rect){
	// check Rect coordinates with intersection of each wall
	for(auto it=this->walls.begin(); it!=this->walls.end(); it=next(it))
	{
		if((*it).intersects(rect)) return true;
	}
	return false;

}

void GameMap::add_wall(sf::FloatRect rect){
	this->walls.push_back(rect);
}


void GameMap::reset(void){
	this->walls.resize(0);
}
