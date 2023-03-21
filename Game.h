#include "pch.h"
#include "Ball.h"
#include "CollideEvent.h"
/*
	Class that act as game engine
*/

using namespace std;

class Game
{
private:
	// variable
	sf::RenderWindow* window;
	sf::Event ev;
	priority_queue<CollideEvent> minPQ;
	float time;
	
	vector<Ball*> ligma;

	// private function
	void initVar();
	void initWindow();

public:
	// constructoe and destructor
	Game();
	virtual ~Game();

	//Accessor
	const bool running() const;

	// function
	void pollevent();

	void predict(Ball *a);

	void spawnBall();
	void simulateGame();
	void renderBall();

	void update();
	void render();
};

