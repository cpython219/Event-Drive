#include "pch.h"
#include "Game.h"
using namespace std;

void Game::initVar()
{
	this->window = nullptr;
	this->time = 0.0;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "gaming", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

//constructor
Game::Game()
{
	this->initVar();
	this->initWindow();
}

//destructor
Game:: ~Game()
{
	delete this->window;
}

//acessor
const bool Game::running() const
{
	return this->window->isOpen();
}

//function
void Game::pollevent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

bool operator < (CollideEvent ev1, CollideEvent ev2) 
{
	return ev1.getTime() > ev2.getTime();
}

void Game::predict(Ball *a)
{
	if (a == nullptr) return;

	for (int i = 0; i < this->ligma.size(); i++) {
		Ball* cur = this->ligma[i];
		float dt = a->timeToHit(cur);
		if (dt != -1)
			this->minPQ.push(CollideEvent(this->time + dt, a, cur));
	}

	float dtX = a->timeToHitVertiWall(this->window);
	float dtY = a->timeToHitHorizonWall(this->window);
	if (dtX != -1) minPQ.push(CollideEvent(this->time + dtX, a, nullptr));
	if (dtY != -1) minPQ.push(CollideEvent(this->time + dtY, nullptr, a));

}

void Game::spawnBall() // init minPQ here too
{
	if (ligma.size() > 0) return;
	for (int i = 0; i < 500; i++)
	{
		float posx = rand() % 550 + rand()%10 + 10;
		float posy = rand() % 550 + rand()%10 + 10;
		ligma.push_back(new Ball(sf::Vector2f(posx, posy)));
	}
	
	for (int i = 0; i < ligma.size(); i++)
		this->predict(ligma[i]);

	minPQ.push(CollideEvent(0.f, nullptr, nullptr));
}

void EventOutput(CollideEvent top) 
{
	cout << top.getTime() << " ";
	if (top.get1st() == nullptr && top.get2nd() == nullptr) cout << "Draw\n";
	else if (top.get1st() == nullptr && top.get2nd() != nullptr) cout << "BounceHorizontal\n";
	else if (top.get1st() != nullptr && top.get2nd() == nullptr) cout << "BounceVertical\n";
	else cout << "BounceBall\n";
}

void debugPQ(priority_queue<CollideEvent> pq)
{
	while (!pq.empty())
	{
		CollideEvent top = pq.top(); pq.pop();
		EventOutput(top);
	}
}

void Game::simulateGame()
{
	//debugPQ(minPQ); exit(0);
	while (!minPQ.empty()) 
	{
		CollideEvent top = minPQ.top(); minPQ.pop();
		//EventOutput(top);
		if (!top.isValid()) continue;
		//cout << "?\n";
		Ball* a = top.get1st();
		Ball* b = top.get2nd();
		
		for (int i = 0; i < ligma.size(); i++)
			ligma[i]->moveByTime(top.getTime() - this->time);
		this->time = top.getTime();

		if (a != nullptr && b != nullptr) a->bounceOff(b);              // ball-ball collision
		else if (a != nullptr && b == nullptr) a->bounceOffVertiWall();   // ball-wall collision
		else if (a == nullptr && b != nullptr) b->bounceOffHorizonWall(); // ball-wall collision
		else if (a == nullptr && b == nullptr)
		{
			minPQ.push(CollideEvent(top.getTime() + 1.f, nullptr, nullptr)); 
			break;
			// pause all at once and draw
		}

		predict(a);
		predict(b);
		
	}
}

void Game::renderBall()
{
	for (auto i : ligma) i->render(this->window);
}

void Game::update()
{

	this->pollevent();
	
	this->spawnBall();
	this->simulateGame();
	
	
}


void Game::render()
{
	this->window->clear();

	this->renderBall();

	this->window->display();
}

