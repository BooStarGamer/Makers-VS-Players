#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

#include "Point.h"
#include "SString.h"

#include "SDL/include/SDL.h"
struct SDL_Rect;

enum class PlayerAnim
{
    IDLE,
    WALK,
    JUMP,
    CLIMB
};

class Player: public Entity
{
public:

    Player();

    bool Update(float dt);

    bool Draw();

    void SetTexture(SDL_Texture *tex);

    void Gravity(float dt);

    bool CollisionLogic();

    SDL_Rect GetBounds() const
    {
        return collider;
    }

private:
    bool CheckCollision(SDL_Rect collision);
    void UpdatePlayerPos();

public:

    SDL_Texture* texture;   // Player spritesheet

    // TODO: Define all animation properties
    PlayerAnim currentAnim;

    SDL_Rect collider;

    int width, height;

    float jumpSpeed = 0.0f;
    bool readyToJump = true;
    bool hitObstacle = false;
};

#endif // __PLAYER_H__
