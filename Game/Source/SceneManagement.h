#ifndef __SCENEMANAGEMENT_H__
#define __SCENEMANAGEMENT_H__

#include "SString.h"

class GuiControl;

enum class SceneType
{
    LOGO,
    TITLE,
    GAMEPLAY,
    ENDING
};

class SceneManagement
{
public:

    SceneManagement() : active(true), loaded(false) {}

    virtual bool Load()
    {
        return true;
    }

    virtual bool Update(float dt)
    {
        return true;
    }

    virtual bool Draw()
    {
        return true;
    }

    virtual bool Unload()
    {
        return true;
    }

public:

    bool active = true;
    SString name;

    bool loaded = false;
};

#endif // __SCENEMANAGEMENT_H__