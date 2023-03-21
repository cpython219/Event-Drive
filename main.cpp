#include "pch.h"
#include "Game.h"
using namespace std;
using namespace sf;

int main()
{
	//init random
	srand(time(NULL));


	//init game
	Game game;

	while (game.running())
	{


		//update
		game.update();

		//render
		game.render();

	}


}


