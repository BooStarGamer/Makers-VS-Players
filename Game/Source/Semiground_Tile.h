#ifndef __SEMIGROUNDTILE_H__
#define __SEMIGROUNDTILE_H__

#include "Point.h"
#include "External/SDL/include/SDL.h"

struct SDL_Texture;
struct SDL_Rect;

class SemigroundTile
{
public: //Functions

	SemigroundTile();

	SemigroundTile(iPoint pos, iPoint coords, bool rot);

	virtual ~SemigroundTile();

	void Draw();

	iPoint GetCoords() const
	{
		return coordinates;
	}

	//SDL_Rect GetRect() const
	//{
	//	return semigroundRect;
	//}

private:
	bool rotated = false;
	SDL_Texture* semigroundTex;

	SDL_Rect semigroundHRect = { 0, 0, 41, 4 };
	SDL_Rect semigroundVLRect = { 0, 0, 4, 41 };
	SDL_Rect semigroundVRRect = { 37, 0, 4, 41 };

	iPoint position = { 0, 0 };
	iPoint coordinates = { 0, 0 };

	SDL_Rect semiground1 = { 0, 0, 41, 41 };
	SDL_Rect semiground2 = { 41, 0, 41, 41 };
	SDL_Rect semiground3 = { 82, 0, 41, 41 };
	SDL_Rect semiground4 = { 123, 0, 41, 41 };
	SDL_Rect semiground5 = { 164, 0, 41, 41 };
};

#endif // __SEMIGROUNDTILE_H__
