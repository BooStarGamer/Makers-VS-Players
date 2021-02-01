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

    void UpdatePlayerPos();

    bool CheckCollision(SDL_Rect collision);

    void CollisionSemisolidLogic();

private:
    void CheckPassThroughX(SDL_Rect p, SDL_Rect ss);
    void Jump();
    void ResetJump();

//Bools------------
private:
    bool jump;
    bool ground;
    bool crouched;
    bool passThroughX = true;
    bool loopSsX = true;

public:
    bool dragged = false;
    bool left = false;
    bool right = false;
//Bools------------

private: //Variables
    int crouchY;

public:
    float speedMultiplier = 1.0f;

public:

    SDL_Texture* texture;   // Player spritesheet

    // TODO: Define all animation properties
    PlayerAnim currentAnim;

    SDL_Rect collider;

    int width, height;

    int jumpForce = 52;

    float jumpSpeed = 0.0f;
    bool readyToJump = true;
    bool hitObstacle = false;
    float finalSpeed = 0.0f;
};

#endif // __PLAYER_H__
