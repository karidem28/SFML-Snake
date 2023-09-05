/*!
* \author Olha Sereda
* \date 2022
* \copyright Olha Sereda (olha.sereda@student.uj.edu.pl)
* \mainpage "Snake Game"
* Example of the snake game with using SFML Library\n
* The main goal of the game is eating the green apples and avoid of walls and self intersection.\n
* \n
* Usage keys:\n
* **Left arrow key** - turn direction counterclock-wise. Continius key pressing accelerates the speed of turn.\n
* **Right arrow key** - turn direction clockwise. Continius key pressing accelerates the speed of turn.\n
* **Up arrow key** - restarts the level after the snake die.\n
* \n
* ![Snake game process](snake1.png) ![Snake game process](snake2.png)
* \n
* \n
* \n
* File **levels.txt** contains level's diagaram:\n
* level contains keyword **Level\#XX** at begin - where XX is index number\n
* Then contains list of box coordinated  - **each line contains one set of wall coodinates**.\n
* and then level description ends by '###' string.\n
* \n
* Example:
* \code
* Level#1
* 0 590 600 10
* 0 0 10 600
* 590 0 10 600
* 0 0 600 10
* ###
* Level#2
* 0 590 600 10
* 0 0 10 600
* 590 0 10 600
* 0 0 600 10
* 295 50 10 500
* ###
* Level#3
* 0 590 600 10
* 0 0 10 600
* 590 0 10 600
* 0 0 600 10
* 295 50 10 500
* 50 295 500 10
* ###
* \endcode
* \n
* The game uses <A HREF="https://www.sfml-dev.org/">SFML</A> library.
*/


#include <iostream>
#include <sstream>
#include <fstream>
#include <random>
#include <vector>
#include <iterator>
#include "SFML/Graphics.hpp"
#include "food.hpp"
#include "game_map.hpp"
#include "snake.hpp"
#include "game.hpp"
#include "beer.hpp"

using namespace sf;
using namespace std;

constexpr auto LEVEL_COUNT = 3;
constexpr auto LEVEL_TIME = 60;  // 60 seconds
constexpr auto SNAKE_INIT_LENGTH = 20;	// 20 segments of snake
constexpr auto SPEED_OF_GAME = 60000;

sf::Clock cl;		///< Game clock timer
float ttime;		///< time elapsed since timer has been restarted
double game_time;	///< time in secondes elapces since level begun
Food *Apple;		///< pointer to the Food
Snake *SnakeHero;	///< pointer to the Hero
int Level;			///< Level index number
Beer* BeerCup;

int game_speed;

/*! Funtrion to load the level data by the level number
* @param GameMap Level object.
* @param path and filename to level data.
* @param level index number.
* @return true if particular level found and level data loadeded
*/
bool load_level(GameMap &m, string filename, int level)
{
	string fline;
	ifstream infile(filename);
	infile.clear();
	infile.seekg(0, ios::beg);	// Set reading file pointer from begin of file
	size_t pos = 0;
	int read_counter=0;
	std::string level_search;

	level_search = "Level#" + to_string(level);
	while(getline(infile,fline))				// Read lines until 
	{
		 pos = fline.find(level_search, 0);		//		level number will be found
		 if(pos!=string::npos) {
				while(getline(infile,fline))	// Begin read of wall Rect data until string contained - "###"
				{
					pos = fline.find(string("###"), 0);

					if(pos==string::npos) {
						std::stringstream iss(fline);	//Load string to stream
						int x1, y1, x2, y2;
						iss >> x1 >> y1 >> x2 >> y2;	// load 4 int attributes from string to variables
						m.add_wall(FloatRect(float(x1), float(y1), float(x2), float(y2)));	// Add new wall to level data
						read_counter++;					//number of readed walls 
					 } else {
						 if(read_counter>0) return true; else return false;
					 }
				}
				if(read_counter>0) return true; else return false;
		 }
	}
	return false;
}

int WinMain()
{
	// Init of game
	Level=1;
	game_time=0;
	game_speed = SPEED_OF_GAME;

	srand(time(NULL));
	SnakeHero = new Snake(Vector2f(100,100),0, SNAKE_INIT_LENGTH);
	GameMap MapLevel;
	load_level(MapLevel,"levels.txt",Level);

	// Create the rendering window with size 600x600 pixels
	RenderWindow window(VideoMode(600, 600), "Super Snake Game");
	//Create the game area object;
	Game game(window.getSize(),"28days_later.ttf", SnakeHero);



	// Main loop until window is not closed.
	while(window.isOpen()){
		//get current time in microseconds elapsed since previous clock restart
		ttime = cl.getElapsedTime().asMicroseconds();
		//get event from the window event's queue.
		Event event;
			while(window.pollEvent(event)){
				//if there was Closed window event then stop the app
				if(event.type == sf::Event::Closed){
					window.close();
				}
			}


			// if the time elapsed since the timer was restarted is greater than game_speed then redraw the screen.
			if(ttime>game_speed)
			{	
				if (BeerCup == nullptr) {
					BeerCup = new Beer(Vector2f(float(rand() % 500 + 50), float(rand() % 500 + 50)));
				}
				// If Apple was not created then choose new random coordinates until
				// their check shows they not crossing with walls.
				// Then create new Food.
				if (Apple==nullptr) {
					FloatRect TmpRect;
					Vector2f TmpCoords;
					do{
						TmpCoords = Vector2f(float(rand()%500+50),float(rand()%500+50));
						TmpCoords -= Vector2f(10,10);

						TmpRect = FloatRect(TmpCoords.x, TmpCoords.y,20,20);
					}while(MapLevel.check_intersection_with_circle(TmpRect)==true);

					Apple = new Food(Vector2f(TmpRect.left, TmpRect.top));
				}

				// Probe events queue for the KeyPressed event
				if (event.type == Event::KeyPressed)
				{
					// LEFT key pressed -> Turn Hero direction to counterclock-wise
					if (event.key.code == Keyboard::Left) {

						SnakeHero->turn_left();
					}

					// RIGHT key pressed -> Turn Hero direction to clock-wise
					if (event.key.code == Keyboard::Right) {
						SnakeHero->turn_right();
					}

					// If Game is in state of 'loose live' of 'game over'
					// tnen wait for key 'UP' to restart the level or game.
					if (Keyboard::isKeyPressed(Keyboard::Up)) {
						if(game.get_state()==1) game.continue_game();
						if(game.get_state()==2) {
							game.reset_game();
							game_speed=60000;
						}
						game_time=0;
					}
				}

				// Reset the delta(turn acceleration) if Key was released
				if(event.type==Event::KeyReleased)
				{
					SnakeHero->reset_delta();
				}


				//begin the draw the scene from the cleaning the rendering window
				window.clear();
				// if game state is 'Normal game' then update the Hero's attributes
				// and draw Hero and Food
				if(game.get_state()==0){
					SnakeHero->update();
					window.draw(*SnakeHero);
					window.draw(*Apple);
					window.draw(*BeerCup);
				}
				// Draw the current level
				window.draw(MapLevel);
				// Draw game scores 
				window.draw(game);

				// display drawn scene on window
				window.display();

				//update game time with system tick (related to SFML documentation)
				game_time+=ttime/1000000;
				//restart the clock timer
				cl.restart();

				//***After scene rendering measures and checks***
				//SnakeHero->self_intersection();
				// Check if Hero eated Apple (disatance between head center and center of apple less then 10 ( in game 
				// the radius of Hero's head and apple = 5, then 5 + 5 = 10))
				//if apple eated then need to grow the tail and destroy old Apple 
				Vector2f DistanceVector;
				DistanceVector = SnakeHero->get_coord() - Apple->get_coord();
				if (std::sqrt(DistanceVector.x * DistanceVector.x + DistanceVector.y * DistanceVector.y)<10.0) {
					delete Apple;
					Apple=nullptr;
					SnakeHero->grow(10);
					game.add_score();
				}

				BeerCup->Update();
				if (!BeerCup->IsAlive()) {
					delete BeerCup;
					BeerCup = nullptr;
				}
				else {
					if (SnakeHero->GetRect().intersects(BeerCup->get_rect())) {
						SnakeHero->grow(30);
						game.add_score();
						game.add_score();
						game.add_score();
						delete BeerCup;
						BeerCup = nullptr;
					}
				}

				//Check if the Hero has bitten his own tail
				//Check if Hero didn't collide with Level walls
				// If yes then recreate Hero, reset scores and lives count 
				if((MapLevel.check_intersection_with_circle(SnakeHero->GetRect())==true) || (SnakeHero->self_intersection()==true)) {
					delete SnakeHero;
					SnakeHero = new Snake(Vector2f(100,100),0, SNAKE_INIT_LENGTH);
					game.reset_score();
					game.hero_died();
					game_time=0;
				}

				// If level game time greate then 60sec and state as 'normal game'
				// then load and switch to new level
				// recreate Hero and remove Apple 
				if(game_time > LEVEL_TIME && game.get_state()==0) {
					game_time=0;	// Reset level time on new level
					Level++;
					if(Level > LEVEL_COUNT) Level = 1;	// Begin from first level if reached last. 
					int size = SnakeHero->get_size();					// Recreate 
					delete SnakeHero;									//			Hero
					SnakeHero = new Snake(Vector2f(100,100),0,size);	//				for new level
					delete Apple;
					Apple=nullptr;
					MapLevel.reset();							// Clear level 
					load_level(MapLevel,"levels.txt",Level);	// Load new level data
					game_speed-=2000;	//Each new level must be faster then previous.
				}
			}
	}

	return 0;
}
