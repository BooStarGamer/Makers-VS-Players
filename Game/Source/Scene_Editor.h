#ifndef __SCENEEDTIOR_H__
#define __SCENEEDITOR_H__

#include "Point.h"
#include "List.h"
#include "External/SDL/include/SDL.h"

#define TILE_SIZE 41
#define WIN_HEIGHT 574
#define WIN_WIDTH 1024
#define H_MARGIN (720 - WIN_HEIGHT) / 2
#define W_MARGIN (1280 - WIN_WIDTH) / 2

struct SDL_Texture;
struct SDL_Rect;

enum LevelAmplitude
{
	AMP0 = 0,
	AMP1,
	AMP2,
	AMP3
};

struct uTile
{
	uTile(SDL_Rect r, iPoint pos);

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

	void DrawGrid();
	void CameraMove();
	void LevelAmpLogic();

private: //Functions
	void DebugMargin(bool debug);
	void SceneEditor::DebugTileset(LevelAmplitude lvlAmp, bool debug);

public: // variables
	bool debugMargin = true;
	bool debugTileset = false;
	SDL_Texture* background = nullptr;

private: //Amplitude
	LevelAmplitude lvlAmp;
	int maxAmp[4] = {0, -WIN_WIDTH, -WIN_WIDTH * 2, -WIN_WIDTH * 3};

private: //Tileset
	List<uTile*> Tileset0;
	List<uTile*> Tileset1;
	List<uTile*> Tileset2;
	List<uTile*> Tileset3;

	uTile* GetTileFromXY(int x, int y, LevelAmplitude lvlAmp);
	iPoint GetMousePosInTile();
};

#endif // __SCENEEDITOR_H__
