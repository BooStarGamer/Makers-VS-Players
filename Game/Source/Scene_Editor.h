#ifndef __SCENEEDTIOR_H__
#define __SCENEEDITOR_H__

class SceneEditor
{
public:

	SceneEditor();

	virtual ~SceneEditor();

	void DrawGrid();

private:
	void DebugMargin(bool debug);

public:
	bool debugMargin = false;
};

#endif // __SCENEEDITOR_H__
