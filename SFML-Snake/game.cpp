/*!
*	\author Olha Sereda
*	\date 2022
*   \copyright Olha Sereda (olha.sereda@student.uj.edu.pl)
*/
#include "game.hpp"

Game::Game(sf::Vector2u coord, std::string fontname, Snake *snake)
{
	this->fontsize=20;
	this->life = 5;
	this->screensize=coord;
	this->state=0;
	this->font.loadFromFile(fontname);
	this->snake=snake;
	this->score=0;

}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::stringstream ss;

	// Render Score data
	ss << " Score " << score;
	sf::Text text(ss.str(), font);
	text.setCharacterSize(this->fontsize);
	text.setFillColor(sf::Color::Red);
	text.setPosition(20,20);
	target.draw(text, states);

	// Render Life data
	ss.str("");
	ss << "Life " << this->life ;
	text.setString(ss.str());
	text.setCharacterSize(this->fontsize);
	text.setFillColor(sf::Color::Red);
	text.setPosition(float(this->screensize.x) - float(ss.str().length()*this->fontsize)/2-20,20);
	target.draw(text, states);
	
	switch(this->state){


		case 2:
			ss.str("GAME OVER");
			text.setString(ss.str());
			text.setCharacterSize(50);
			text.setFillColor(sf::Color::Blue);
			text.setPosition(float(this->screensize.x)/2 - float(ss.str().length()*50)/4,float(this->screensize.y)/2);
			target.draw(text, states);

		case 1:
			ss.str("Press UP to continue");
			text.setString(ss.str());
			text.setCharacterSize(50);
			text.setFillColor(sf::Color::White);
			text.setPosition(float(this->screensize.x)/2 - float(ss.str().length()*45)/4, float(this->screensize.y)/2+50);
			target.draw(text, states);
			break;
		default:
			break;
	}

//	target.draw(cir, states);
}

int Game::get_state(void){
	return this->state;
}

void Game::set_state(int state){
	this->state=state;
}

void Game::add_score(void){
	this->score++;
}

void Game::reset_score(void){
	this->score=0;
}

void Game::hero_died(void){
	this->life--;
	set_state(1);

	if(life<0){
		set_state(2);
		life=0;
	}
}

void Game::continue_game(void){
	set_state(0);
}

void Game::reset_game(void){
	this->score=0;
	this->life=5;
	set_state(0);
}
