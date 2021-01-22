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
#define UP_MAXIMUM (H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2)

struct SDL_Texture;
struct SDL_Rect;
class GroundTile;

enum TileType
{
	NO_TILE = -1,
	ERASE,
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
	void EraseTileLogic();
	void TileSelectedLogic();
	void EditModeLogic();

private:
	void DrawGrid();
	void DrawTiles();
	void PlaceTile(TileType type, iPoint pos, iPoint coords);
	void EraseTile(TileType type, iPoint coords);
	DebugTile* GetTileFromXY(int x, int y, LevelAmplitude lvlAmp);
	iPoint GetMousePosInTile();
	iPoint GetMouseCoordInTile();
	iPoint GetPosFromCoords(iPoint coords);

public: //Getters
	bool GetEditMode() const
	{
		return editMode;
	}

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
	bool editMode = true;
	TileType selectedTile = NO_TILE;
//Variables----------

private: //Amplitude
	LevelAmplitude lvlAmp;
	int maxAmp[4] = {0, -WIN_WIDTH, -WIN_WIDTH * 2, -WIN_WIDTH * 3};

//Lists--------------
public:
	List<GroundTile*> groundTiles;

private: //Debug Tileset
	List<DebugTile*> Tileset0;
	List<DebugTile*> Tileset1;
	List<DebugTile*> Tileset2;
	List<DebugTile*> Tileset3;
//Lists--------------
};

#endif // __SCENEEDITOR_H__
