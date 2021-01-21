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

	GroundTile(int x, int y);

	virtual ~GroundTile();

	void Draw();

	void TypeGroundLogic();

private:
	SDL_Texture* groundTex;
	SDL_Rect groundRect = {0, 0, 41, 41};
	iPoint position = {0, 0};
	SDL_Rect typeRect = {0, 0, 41, 41};
};

#endif // __GROUNDTILE_H__
