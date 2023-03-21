#include "pch.h"
#include "Ball.h"


//private function
void Ball::initShape()
{
	this->shape.setRadius(5.f);
	this->shape.setFillColor(sf::Color::White);
	this->shape.setOutlineThickness(1);
}

void Ball::initPos(sf::Vector2f pos)
{
	float rad = this->shape.getRadius();
	this->shape.setOrigin(rad, rad);
	this->shape.setPosition(pos);
}

void Ball::initVar()
{
	this->collisionCount = 0;
	this->mass = 0.5f;

	// random ball speed
	this->speed.x = rand() % 5;
	this->speed.y = sqrt(30 - this->speed.x * this->speed.x);
	if (rand() % 2) this->speed.x *= -1;
	if (rand() % 2) this->speed.y *= -1;

	//this->speed.x = 1; this->speed.y = -5;

}

//constructor / destructoe
Ball::Ball(sf::Vector2f pos)
{
	this->initShape();
	this->initPos(pos);
	this->initVar();
}

Ball::~Ball()
{

}

int Ball::countCollision()
{
	return this->collisionCount;
}

//function

void Ball::moveByTime(float dt)
{
	this->shape.move(this->speed.x * dt, this->speed.y * dt);
}

float Ball::timeToHit(Ball *other)
{
	if (this == other) return -1;
	sf::Vector2f posThis = this->shape.getPosition();
	sf::Vector2f posOther = other->shape.getPosition();
	float dx = posOther.x - posThis.x;
	float dy = posOther.y - posThis.y;
	float dvx = other->speed.x - this->speed.x;
	float dvy = other->speed.y - this->speed.y;
	float dvdr = dx * dvx + dy * dvy;
	if (dvdr > 0) return -1;
	float dvdv = dvx * dvx + dvy * dvy;
	if (dvdv == 0) return -1;
	float drdr = dx * dx + dy * dy;
	float sigma = this->shape.getRadius() + other->shape.getRadius();
	float d = (dvdr * dvdr) - dvdv * (drdr - sigma * sigma);
	//if (drdr < sigma * sigma) cout << "Overlap Ball";
	if (d < 0) return -1;
	return -(dvdr + sqrt(d)) / dvdv;
}

float Ball::timeToHitVertiWall(sf::RenderTarget* window)
{
	sf::Vector2f posThis = this->shape.getPosition();
	float rad = this->shape.getRadius();
	float vx = this->speed.x;
	if (vx > 0) return (window->getSize().x - posThis.x - rad) / vx;
	else if (vx < 0) return (rad - posThis.x) / vx;
	return -1;
}

float Ball::timeToHitHorizonWall(sf::RenderTarget* window)
{
	sf::Vector2f posThis = this->shape.getPosition();
	float rad = this->shape.getRadius();
	float vy = this->speed.y;
	if (vy > 0) return (window->getSize().y - posThis.y - rad) / vy;
	else if (vy < 0) return (rad - posThis.y) / vy;
	return -1;
}

void Ball::bounceOff(Ball* other)
{
	if (this == other) return;
	sf::Vector2f posThis = this->shape.getPosition();
	sf::Vector2f posOther = other->shape.getPosition();
	float dx = posOther.x - posThis.x;
	float dy = posOther.y - posThis.y;
	float dvx = other->speed.x - this->speed.x;
	float dvy = other->speed.y - this->speed.y;
	float dvdr = dx * dvx + dy * dvy;
	// distance between ball centers at collison
	float dist = this->shape.getRadius() + other->shape.getRadius();

	// magnitude of normal force
	float magnitude = 2 * this->mass * other->mass * dvdr / ((this->mass + other->mass) * dist);

	// normal force, and in x and y directions
	float fx = magnitude * dx / dist;
	float fy = magnitude * dy / dist;

	// update velocities according to normal force
	this->speed.x += fx / this->mass;
	this->speed.y += fy / this->mass;
	other->speed.x -= fx / other->mass;
	other->speed.y -= fy / other->mass;

	// update collision counts
	this->collisionCount++;
	other->collisionCount++;
}

void Ball::bounceOffVertiWall()
{
	this->speed.x *= -1; 
	this->collisionCount++;
}

void Ball::bounceOffHorizonWall()
{
	this->speed.y *= -1;
	this->collisionCount++;
}

void Ball::update()
{
	//cout << this->shape.getPosition().x << " " << this->shape.getPosition().y << "\n";
	
	this->shape.move(this->speed);
	
}



void Ball::render(sf::RenderTarget* window)
{
	window->draw(this->shape);
}

