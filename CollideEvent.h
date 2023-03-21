#include "Ball.h"


class CollideEvent
{
private:
	// variable
	float time;
	int countA, countB;
	Ball* a, *b;

	// private function

public:
	// constructor / destructor
	CollideEvent(float time,Ball *a,Ball *b);


	// accessor
	float getTime();
	Ball* get1st();
	Ball* get2nd();


	// function
	bool operator < (CollideEvent *other) {
		return this->time > other->time;
	}
	bool isValid();
};

