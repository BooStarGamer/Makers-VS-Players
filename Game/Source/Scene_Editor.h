#ifndef __SCENEEDTIOR_H__
#define __SCENEEDITOR_H__

#define TILE_SIZE 41
#define WIN_HEIGHT 574
#define WIN_WIDTH 1024
#define H_MARGIN (720 - WIN_HEIGHT) / 2
#define W_MARGIN (1280 - WIN_WIDTH) / 2

enum LevelAmplitude
{
	AMP0 = 0,
	AMP1,
	AMP2,
	AMP3
};

class SceneEditor
{
public:

	SceneEditor();
	SceneEditor(LevelAmplitude lvl);

	virtual ~SceneEditor();

	void DrawGrid();
	void CameraMove();
	void LevelAmpLogic();

private:
	void DebugMargin(bool debug);

public:
	bool debugMargin = false;

private:
	LevelAmplitude lvlAmp;
	int maxAmp[4] = {0, -WIN_WIDTH, -WIN_WIDTH * 2, -WIN_WIDTH * 3};
};

#endif // __SCENEEDITOR_H__
