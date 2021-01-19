#ifndef __GUIMANAGER_H__
#define __GUIMANAGER_H__

#include "Module.h"
#include "GuiControl.h"

#include "List.h"

struct SDL_Texture;

class GuiManager : public Module
{
public:

	GuiManager();

	virtual ~GuiManager();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	GuiControl* CreateGuiControl(GuiControlType type);
	void DestroyGuiControl(GuiControl* entity);

	void AddGuiControl(GuiControl* entity);

public:

	List<GuiControl*> controls;
	bool debugGui = false;

public: //Textures
	SDL_Texture* buttonSpriteSheet = nullptr;
	SDL_Texture* checkBoxSpriteSheet = nullptr;
	SDL_Texture* sliderSpriteSheet = nullptr;

public: //Others

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;
};

#endif // __GUIMANAGER_H__
