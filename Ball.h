#pragma once


class Ball
{
private:
	// variable
	sf::CircleShape shape;
	sf::Vector2f speed;
	int collisionCount;
	float mass;

	//private funtion
	void initShape();
	void initPos(sf::Vector2f pos);
	void initVar();

public:
	//constructor / destructor
	Ball(sf::Vector2f pos);
	virtual ~Ball();

	//accessor
	int countCollision();

	//function
	void moveByTime(float dt);
	
	float timeToHit(Ball *other);
	float timeToHitVertiWall(sf::RenderTarget* window);
	float timeToHitHorizonWall(sf::RenderTarget* window);

	void bounceOff(Ball* other);
	void bounceOffVertiWall();
	void bounceOffHorizonWall();

	void update();
	void render(sf::RenderTarget* window);
};

