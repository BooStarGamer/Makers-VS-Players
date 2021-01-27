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
    position = { 41 * 6, 41 * 10 };
    jumpSpeed = 2.0f;
    jumpForce = JUMP_FORCE;
    speedMultiplier = 1.0f;
    dragged = false;

    width = 38;
    height = 79;

    collider = { position.x, position.y, width, height };

    // Define Player animations
}

bool Player::Update(float dt)
{
    #define GRAVITY 5.0f
    #define PLAYER_MOVE_SPEED 3.0f
    float speed = PLAYER_MOVE_SPEED;

    UpdatePlayerPos();

    if (!app->scene->sceneEditor->GetEditMode())
    {
        if (app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
        {
            speed = speed * speedMultiplier;
            if (speedMultiplier < 2.0f)
            {
                speedMultiplier += 0.02f;
            }
            else
            {
                speedMultiplier = 2.0f;
            }
        }
        else if (app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_IDLE)
        {
            speed = speed * speedMultiplier;
            if (speedMultiplier > 1.0f)
            {
                speedMultiplier -= 0.04f;
            }
            else
            {
                speedMultiplier = 1.0f;
            }
        }

        if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
        {
            left = true; 
            right = true;
        }
        else if (collider.x > W_MARGIN && app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
        {
            if (!crouched && !jump)
            {
                if (ground) collider.x -= (speed * dt);
                else if (!ground)
                {
                    collider.x -= ((speed + PLAYER_MOVE_SPEED) * dt);
                    speed += PLAYER_MOVE_SPEED;
                }
                if (!CollisionLogic())
                {
                    position.x = collider.x;
                }
                else
                {
                    collider.x = position.x;
                }
            }
            else if (crouched && jump)
            {
                if (ground) collider.x -= (speed * dt);
                else if (!ground)
                {
                    collider.x -= ((speed + PLAYER_MOVE_SPEED) * dt);
                    speed += PLAYER_MOVE_SPEED;
                }
                if (!CollisionLogic())
                {
                    position.x = collider.x;
                }
                else
                {
                    collider.x = position.x;
                }
            }
            else if (!crouched && jump)
            {
                if (ground) collider.x -= (speed * dt);
                else if (!ground)
                {
                    collider.x -= ((speed + PLAYER_MOVE_SPEED) * dt);
                    speed += PLAYER_MOVE_SPEED;
                }
                if (!CollisionLogic())
                {
                    position.x = collider.x;
                }
                else
                {
                    collider.x = position.x;
                }
            }
        }
        else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP) left = false;

        if (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
        {
            right = true;
            left = false;
        }
        else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
        {
            if (!crouched && !jump)
            {
                if (ground) collider.x += (speed * dt);
                else if (!ground)
                {
                    collider.x += ((speed + PLAYER_MOVE_SPEED) * dt);
                    speed += PLAYER_MOVE_SPEED;
                }
                if (!CollisionLogic())
                {
                    position.x = collider.x;
                }
                else
                {
                    collider.x = position.x;
                }
            }
            else if (crouched && jump)
            {
                if (ground) collider.x += (speed * dt);
                else if (!ground)
                {
                    collider.x += ((speed + PLAYER_MOVE_SPEED) * dt);
                    speed += PLAYER_MOVE_SPEED;
                }
                if (!CollisionLogic())
                {
                    position.x = collider.x;
                }
                else
                {
                    collider.x = position.x;
                }
            }
            else if (!crouched && jump)
            {
                if (ground) collider.x += (speed * dt);
                else if (!ground)
                {
                    collider.x += ((speed + PLAYER_MOVE_SPEED) * dt);
                    speed += PLAYER_MOVE_SPEED;
                }
                if (!CollisionLogic())
                {
                    position.x = collider.x;
                }
                else
                {
                    collider.x = position.x;
                }
            }
        }
        else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP) right = false;

        if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
        {
            collider.h = 32;
            collider.y = collider.y + 47;
            UpdatePlayerPos();
            crouched = true;
        }
        else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_UP)
        {
            collider.h = 79;
            collider.y = collider.y - 47;
            UpdatePlayerPos();
            crouched = false;
        }

        if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && ground)
        {
            ground = false;
            jump = true;
        }

        if (jump) Jump();

        Gravity(dt);

        finalSpeed = abs(speed);
    }
    else
    {
        if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
        {
            if (app->render->camera.x - WIN_WIDTH > app->scene->sceneEditor->GetAmpLength((LevelAmplitude)((int)app->scene->sceneEditor->GetLevelAmplitude() + 1)) + W_MARGIN)
            {
                collider.x += ((PLAYER_MOVE_SPEED + 1) * dt);
            }
        }
        
        if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
        {
            if (-app->render->camera.x + W_MARGIN > W_MARGIN )
            {
                collider.x -= ((PLAYER_MOVE_SPEED + 1) * dt);
            }
        }

        if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && -app->render->camera.y + H_MARGIN > UP_MAXIMUM) collider.y -= ((PLAYER_MOVE_SPEED + 1) * dt);

        if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && -1 * (app->render->camera.y - WIN_HEIGHT - H_MARGIN) < WIN_HEIGHT + H_MARGIN) collider.y += ((PLAYER_MOVE_SPEED + 1) * dt);
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
    }
    else
    {
        collider.y = position.y;
        jumpSpeed = 2.0f;
        //jumpForce = JUMP_FORCE;
    }
}

bool Player::CollisionLogic()
{
    ListItem<GroundTile*>* list;
    for (list = app->scene->sceneEditor->groundTiles.start; list != nullptr; list = list->next)
    {
        if (CheckCollision(list->data->GetRect()))
        {
            ground = true;
            return true;
        }
    }

    return false;
}

bool Player::CheckCollision(SDL_Rect collision)
{
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
    if (ground)
    {
        jump = false;
        jumpForce = JUMP_FORCE;
    }
}
