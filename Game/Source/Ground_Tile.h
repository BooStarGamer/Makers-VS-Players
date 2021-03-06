#ifndef __GROUNDTILE_H__
#define __GROUNDTILE_H__

#include "Point.h"
#include "External/SDL/include/SDL.h"

struct SDL_Texture;
struct SDL_Rect;

class GroundTile
{
public: //Functions

	GroundTile();

	GroundTile(iPoint pos, iPoint coords);

	virtual ~GroundTile();

	void Draw();

	iPoint GetCoords() const
	{
		return coordinates;
	}

	SDL_Rect GetRect() const
	{
		return groundRect;
	}

private:
	SDL_Texture* groundTex;
	SDL_Rect groundRect = {0, 0, 41, 41};
	iPoint position = {0, 0};
	iPoint coordinates = {0, 0};
	SDL_Rect ground1 = {0, 0, 41, 41};
	SDL_Rect ground2 = { 41, 0, 41, 41 };
	SDL_Rect ground3 = { 82, 0, 41, 41 };
	SDL_Rect ground4 = { 123, 0, 41, 41 };
	SDL_Rect ground5 = { 164, 0, 41, 41 };
	SDL_Rect ground6 = { 205, 0, 41, 41 };
	SDL_Rect ground7 = { 246, 0, 41, 41 };
	SDL_Rect ground8 = { 287, 0, 41, 41 };
	SDL_Rect ground9 = { 328, 0, 41, 41 };
	SDL_Rect ground10 = { 369, 0, 41, 41 };
	SDL_Rect ground11 = { 410, 0, 41, 41 };
	SDL_Rect ground12 = { 451, 0, 41, 41 };
	SDL_Rect ground13 = { 492, 0, 41, 41 };
	SDL_Rect ground14 = { 533, 0, 41, 41 };
	SDL_Rect ground15 = { 574, 0, 41, 41 };
};

#endif // __GROUNDTILE_H__
