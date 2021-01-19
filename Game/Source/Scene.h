#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "SceneManagement.h"

class GuiButton;
class GuiSlider;
class GuiCheckBox;
class GuiString;

enum Scenes
{
	MAIN_MENU
};

class Scene : public Module
{
public:

	Scene();

	virtual ~Scene();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

private:
	bool OnGuiMouseClickEvent(GuiControl* control);

	Scenes currScene;

	GuiCheckBox* test = nullptr;
};

#endif // __SCENE_H__