/*!
*	\author Olha Sereda
*	\date 2022
*   \copyright Olha Sereda (olha.sereda@student.uj.edu.pl)
*/
#include "snake.hpp"

Snake::Snake(sf::Vector2f coords, float angle, int size=20)
{
	this->color = sf::Color::Red;
	this->delta=1;
	this->speed=2;
	this->angle=angle;
	this->size = size;
	this->path.resize(this->size);
	this->path[0]=coords;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	sf::CircleShape cir;
	// draw all sections of Snake Hero
	   for(int i=this->path.size()-1; i>=0; i-- )
	   {
		   cir.setRadius(5);
		   cir.setOutlineColor(this->color);
		   cir.setOutlineThickness(1);
		   cir.setPosition(this->path[i]);
		   cir.setOrigin(5,5);
		   target.draw(cir, states);
	   }
}

sf::Vector2f Snake::CalcDiff(float deg, float lenght)
{
	//calculate new vector with shift to new coords using lenght and angle 
	return sf::Vector2f(lenght*sin(-0.01745f*deg),lenght*cos(deg*0.01745f));
}

void Snake::turn_left(){
	//decrease of Snake Hero's direction angle with 'delta'
	this->angle-=this->delta;
	//increase delta on each turn to make accelerate effect
	this->delta+=0.5;
}

void Snake::turn_right(){
	//increase of Snake Hero's direction angle with 'delta'
	this->angle+=this->delta;
	//increase delta on each turn to make accelerate effect
	this->delta+=0.5;
}

void Snake::reset_delta()
{
	//set delta to default minimal angle
	this->delta=1;
}


void Snake::update(){
	//add new array element with new coords to the begin of array
	this->path.insert(this->path.begin(),this->path[0] + this->CalcDiff(this->angle,this->speed));
	// if the count of sections of Snake Hero in array greater or equal then size of Hero 
	//   then remove one element from tail's end
	if(this->size<=this->path.size()){
		this->path.pop_back();
	 }

	// inserting new element with new coords to head and removing one element from end makes movement effect
}

void Snake::grow(unsigned int size){
	this->size+=size;
}

sf::Vector2f Snake::get_coord(void){
	return this->path[0];
}

sf::FloatRect Snake::GetRect(void){

	return sf::FloatRect(path[0].x-5,path[0].y-5,10,10);
}


bool Snake::self_intersection(void){
	//begin do checking from the 10th segment of tail
	for(auto it=this->path.begin()+10; it!=this->path.end(); it=next(it))
	{
		sf::Vector2f CenterOfSnakeHead=(*path.begin())-(*it);
		//if distance from center of head to the any of segment of tail <10 then it intersected with tail
		if(std::sqrt(CenterOfSnakeHead.x * CenterOfSnakeHead.x + CenterOfSnakeHead.y * CenterOfSnakeHead.y)<10.0){
			//this->color = sf::Color::Blue;  //change snake color to blue in case of intersection
			return true;
		}
	}
	return false;
}


int Snake::get_size(void){
	return this->size;
}
