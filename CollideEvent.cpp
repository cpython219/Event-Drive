#include "pch.h"
#include "CollideEvent.h"

CollideEvent::CollideEvent(float time,Ball *a,Ball *b)
{
	this->time = time; 
	this->a = a;
	this->b = b;

	if (a != nullptr) this->countA = a->countCollision();
	else this->countA = -1;
	if (b != nullptr) this->countB = b->countCollision();
	else this->countB = -1;
}

float CollideEvent::getTime()
{
	return this->time;
}

Ball* CollideEvent::get1st()
{
	return this->a;
}

Ball* CollideEvent::get2nd()
{
	return this->b;
}

bool CollideEvent::isValid()
{
	//cout << "Pointer Checking: "<<this->a << " " << this->b << " "<<this->countB<<" "<<this->a->countCollision();
	if (this->a != nullptr && this->countA != this->a->countCollision()) return false;
	if (this->b != nullptr && this->countB != this->b->countCollision()) return false;
	return true;
}
