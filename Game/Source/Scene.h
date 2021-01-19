#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "SceneManagement.h"

class GuiButton;

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

};

#endif // __SCENE_H__