#ifndef __SCENEEDTIOR_H__
#define __SCENEEDITOR_H__

#include "Point.h"
#include "List.h"
#include "External/SDL/include/SDL.h"

#include "Ground_Tile.h"

#define TILE_SIZE 41
#define WIN_HEIGHT 574
#define WIN_WIDTH 1024
#define H_MARGIN (720 - WIN_HEIGHT) / 2
#define W_MARGIN (1280 - WIN_WIDTH) / 2

struct SDL_Texture;
struct SDL_Rect;
class GroundTile;

enum TileType
{
	GROUND
};

enum LevelAmplitude
{
	AMP0 = 0,
	AMP1,
	AMP2,
	AMP3
};

struct DebugTile
{
	DebugTile(SDL_Rect r, iPoint pos);

	SDL_Rect tileRect;
	iPoint position;
};

class SceneEditor
{
public: //Functions

	SceneEditor();
	SceneEditor(LevelAmplitude lvl);

	virtual ~SceneEditor();

	void Draw();

	void CleanUp();

//Functions----------
public:
	void CameraMoveLogic();
	void LevelAmpLogic();
	void PlaceTileLogic();

private:
	void DrawGrid();
	void DrawTiles();
	void PlaceTile(TileType type, int x, int y);
	DebugTile* GetTileFromXY(int x, int y, LevelAmplitude lvlAmp);
	iPoint GetMousePosInTile();
	iPoint GetMouseCoordInTile();
	iPoint GetPosFromCoords(iPoint coords);

private: //Debug Functions
	void DebugMargin(bool debug);
	void DebugTileset(LevelAmplitude lvlAmp, bool debug);
//Functions----------

//Variables----------
public:
	bool debugMargin = true;
	bool debugTileset = false;
	SDL_Texture* background = nullptr;

private:
	TileType selectedTile;
//Variables----------

private: //Amplitude
	LevelAmplitude lvlAmp;
	int maxAmp[4] = {0, -WIN_WIDTH, -WIN_WIDTH * 2, -WIN_WIDTH * 3};

//Lists--------------
private:
	List<GroundTile*> groundTiles;

private: //Debug Tileset
	List<DebugTile*> Tileset0;
	List<DebugTile*> Tileset1;
	List<DebugTile*> Tileset2;
	List<DebugTile*> Tileset3;
//Lists--------------
};

#endif // __SCENEEDITOR_H__
