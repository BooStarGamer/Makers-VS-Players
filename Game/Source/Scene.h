#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

class GuiButton;
class GuiSlider;
class GuiCheckBox;
class GuiString;
struct SDL_Texture;

class SceneEditor;

enum Scenes
{
	NONE = -1,
	LOGO_SCENE,
	MAIN_MENU,
	EDITOR_SCENE
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

	Scenes GetCurrScene() const
	{
		return currScene;
	}

private: //Scene Manager

	SceneEditor* sceneEditor;

	Scenes currScene = NONE;
	Scenes prevScene = NONE;

	void SetScene(Scenes scene);

	//Setters
	void SetLogoScene();
	void SetMainMenu();
	void SetEditor();

	//Updaters
	void UpdateLogoScene();
	void UpdateMainMenu();
	void UpdateEditor();


private:
	bool OnGuiMouseClickEvent(GuiControl* control);

	GuiSlider* testSlider;
};

#endif // __SCENE_H__