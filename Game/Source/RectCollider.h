#ifndef __RECTCOLLIDER_H__
#define __RECTCOLLIDER_H__

#include "Module.h"
#include "List.h"
#include "SString.h"

struct SDL_Rect;

class RectCollider
{
public:
	RectCollider(SDL_Rect rectangle, Module* listener = nullptr) : r1(rectangle), listener(listener) {}

public:

	double distance(int x1, int y1, int x2, int y2)
	{
		//Return the distance between the two points
		return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	}

	//Variables
	SDL_Rect r1;
	bool pendingToDelete = false;
	Module* listener = nullptr;

	bool CheckCollision(SDL_Rect r1, SDL_Rect r2) const
	{
		if ((r1.x > r2.x + r2.w) || (r1.x + r1.w < r2.x) || (r1.y > r2.y + r2.h) || (r1.y + r1.h < r2.y))
		{
			return false;
		}
		return true;
	}

	//Collision with SphCollider

	//bool CheckCollision(CircleCollider& a, SDL_Rect& b)
	//{
	//	//Closest point on collision box
	//	int cX, cY;

	//	//Find closest x offset
	//	if (a.x < b.x)
	//	{
	//		cX = b.x;
	//	}
	//	else if (a.x > b.x + b.w)
	//	{
	//		cX = b.x + b.w;
	//	}
	//	else
	//	{
	//		cX = a.x;
	//	}
	//	//Find closest y offset
	//	if (a.y < b.y)
	//	{
	//		cY = b.y;
	//	}
	//	else if (a.y > b.y + b.h)
	//	{
	//		cY = b.y + b.h;
	//	}
	//	else
	//	{
	//		cY = a.y;
	//	}

	//	//If the closest point is inside the circle
	//	if (int dist = distance(a.x, a.y, cX, cY) < a.radius)
	//	{
	//		//This box and the circle have collided
	//		if (dist == 0.0f)
	//			return false;
	//		return true;
	//	}
	//	//If the shapes have not collided
	//	return false;
	//}

	void SetPos(int x, int y)
	{
		r1.x = x;
		r1.y = y;
	}
};

#endif
