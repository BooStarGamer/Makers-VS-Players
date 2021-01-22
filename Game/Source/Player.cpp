#include "App.h"
#include "Input.h"
#include "Render.h"
#include "Player.h"
#include "Scene.h"
#include "Scene_Editor.h"

#include "Log.h"

#define JUMP_FORCE 57
#define JUMP_SUBST 5

Player::Player() : Entity(EntityType::PLAYER)
{
    texture = NULL;
    position = iPoint(12 * 16, 27 * 16);
    jumpSpeed = 2.0f;
    jumpForce = JUMP_FORCE;

    width = 16;
    height = 32;

    collider = { position.x, position.y, width, height };

    // Define Player animations
}

bool Player::Update(float dt)
{
    #define GRAVITY 5.0f
    #define PLAYER_MOVE_SPEED 3.0f
    int speed = PLAYER_MOVE_SPEED;

    UpdatePlayerPos();

    if (!app->scene->sceneEditor->GetEditMode())
    {
        if (app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
        {
            speed = speed * 2;
        }

        if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
        {
            if (ground) collider.x -= (speed * dt);
            else if (!ground) collider.x -= ((speed + PLAYER_MOVE_SPEED) * dt);
            if (!CollisionLogic())
            {
                position.x = collider.x;
            }
            else
            {
                collider.x = position.x;
            }
        }

        if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
        {
            if (ground) collider.x += (speed * dt);
            else if (!ground) collider.x += ((speed + PLAYER_MOVE_SPEED) * dt);
            if (!CollisionLogic())
            {
                position.x = collider.x;
            }
            else
            {
                collider.x = position.x;
            }
        }

        if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && ground)
        {
            jump = true;
        }

        if (jump) Jump();

        Gravity(dt);
    }
    else
    {
        if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) collider.x -= (PLAYER_MOVE_SPEED * 2 * dt);
        if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) collider.x += (PLAYER_MOVE_SPEED * 2 * dt);
        if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) collider.y -= (PLAYER_MOVE_SPEED * 2 * dt);
        if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) collider.y += (PLAYER_MOVE_SPEED * 2 * dt);
    }

    return true;
}

bool Player::Draw()
{
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
    //SDL_Rect rec = { 0 };
    //render->DrawTexture(texture, position.x, position.y, rec);

    app->render->DrawRectangle(collider, { 255, 0, 0, 255 });

    return false;
}

void Player::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

void Player::Gravity(float dt)
{
    if (jumpSpeed < 10) jumpSpeed += GRAVITY * dt;
    collider.y += (jumpSpeed * dt);

    if (!CollisionLogic())
    {
        position.y = collider.y;
        ground = false;
    }
    else
    {
        collider.y = position.y;
        jumpSpeed = 2.0f;
        jumpForce = JUMP_FORCE;
        ground = true;
    }
}

bool Player::CollisionLogic()
{
    ListItem<GroundTile*>* list;
    for (list = app->scene->sceneEditor->groundTiles.start; list != nullptr; list = list->next)
    {
        if (CheckCollision(list->data->GetRect()))
        {
            return true;
        }
    }

    return false;
}

bool Player::CheckCollision(SDL_Rect collision)
{
    //Up collision platforms
    /*if ((GetBounds().y + GetBounds().h) > collision.y && (GetBounds().x + GetBounds().w) > collision.x && 
        GetBounds().y < (collision.y + collision.h) && GetBounds().x < (collision.x + collision.w))
    {
        return true;
    }*/

    if ((collider.y + collider.h) > collision.y &&
        (collider.x + collider.w) > collision.x &&
        collider.y < (collision.y + collision.h) &&
        collider.x < (collision.x + collision.w))
    {
        return true;
    }

    return false;
}

void Player::UpdatePlayerPos()
{
    position.x = collider.x;
    position.y = collider.y;
}

void Player::Jump()
{
    jumpForce -= JUMP_SUBST;
    collider.y -= jumpForce;

    if (jumpForce < 0)
    {
        ResetJump();
    }
}

void Player::ResetJump()
{
    jump = false;
    jumpForce = JUMP_FORCE;
}
