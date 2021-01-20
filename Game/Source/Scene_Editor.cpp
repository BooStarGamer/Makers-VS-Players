#include "App.h"
#include "Scene_Editor.h"
#include "Render.h"
#include "Input.h"
#include "Window.h"

#include "Log.h"

SceneEditor::SceneEditor()
{

}

SceneEditor::SceneEditor(LevelAmplitude lvl)
{
	lvlAmp = lvl;
}

SceneEditor::~SceneEditor()
{
}

void SceneEditor::DrawGrid()
{
	DebugMargin(debugMargin);

	for (int i = 0; i < 26; i++)
	{
		app->render->DrawLine(W_MARGIN + (41 * i), H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2, W_MARGIN + (41 * i), H_MARGIN + WIN_HEIGHT, { 255, 255, 255, 255 });
	}
	for (int i = 0; i < 27; i++)
	{
		app->render->DrawLine(W_MARGIN, H_MARGIN + (41 * i) - WIN_HEIGHT + TILE_SIZE * 2, WIN_WIDTH + W_MARGIN, H_MARGIN + (41 * i) - WIN_HEIGHT + TILE_SIZE * 2, { 255, 255, 255, 255 });
	}

	if (lvlAmp > 0)
	{
		for (int i = 1; i < 26; i++)
		{
			app->render->DrawLine(W_MARGIN + (41 * i) + WIN_WIDTH, H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2, W_MARGIN + (41 * i) + WIN_WIDTH, H_MARGIN + WIN_HEIGHT, { 255, 255, 255, 255 });
		}
		for (int i = 0; i < 27; i++)
		{
			app->render->DrawLine(W_MARGIN + WIN_WIDTH, H_MARGIN + (41 * i) - WIN_HEIGHT + TILE_SIZE * 2, WIN_WIDTH + W_MARGIN + WIN_WIDTH, H_MARGIN + (41 * i) - WIN_HEIGHT + TILE_SIZE * 2, { 255, 255, 255, 255 });
		}
	}

	if (lvlAmp > 1)
	{
		for (int i = 1; i < 26; i++)
		{
			app->render->DrawLine(W_MARGIN + (41 * i) + WIN_WIDTH * 2, H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2, W_MARGIN + (41 * i) + WIN_WIDTH * 2, H_MARGIN + WIN_HEIGHT, { 255, 255, 255, 255 });
		}
		for (int i = 0; i < 27; i++)
		{
			app->render->DrawLine(W_MARGIN + WIN_WIDTH * 2, H_MARGIN + (41 * i) - WIN_HEIGHT + TILE_SIZE * 2, WIN_WIDTH + W_MARGIN + WIN_WIDTH * 2, H_MARGIN + (41 * i) - WIN_HEIGHT + TILE_SIZE * 2, { 255, 255, 255, 255 });
		}
	}

	if (lvlAmp > 2)
	{
		for (int i = 1; i < 26; i++)
		{
			app->render->DrawLine(W_MARGIN + (41 * i) + WIN_WIDTH * 3, H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2, W_MARGIN + (41 * i) + WIN_WIDTH * 3, H_MARGIN + WIN_HEIGHT, { 255, 255, 255, 255 });
		}
		for (int i = 0; i < 27; i++)
		{
			app->render->DrawLine(W_MARGIN + WIN_WIDTH * 3, H_MARGIN + (41 * i) - WIN_HEIGHT + TILE_SIZE * 2, WIN_WIDTH + W_MARGIN + WIN_WIDTH * 3, H_MARGIN + (41 * i) - WIN_HEIGHT + TILE_SIZE * 2, { 255, 255, 255, 255 });
		}
	}
}

void SceneEditor::CameraMove()
{
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (app->render->camera.x < 0) app->render->camera.x += 3;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (app->render->camera.x > maxAmp[lvlAmp]) app->render->camera.x -= 3;
	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if (app->render->camera.y < WIN_HEIGHT - H_MARGIN - 10) app->render->camera.y += 3;
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		if (app->render->camera.y > 0) app->render->camera.y -= 3;
	}

	LOG("CAM: %d", app->render->camera.y);
	LOG("MAX: %d", WIN_HEIGHT - H_MARGIN);
}

void SceneEditor::LevelAmpLogic()
{
	if (app->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN)
	{
		if (lvlAmp != AMP3) lvlAmp = (LevelAmplitude)((int)lvlAmp + 1);
	}

	if (app->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN)
	{
		if (lvlAmp != AMP0) lvlAmp = (LevelAmplitude)((int)lvlAmp - 1);

		if (lvlAmp == AMP2 && app->render->camera.x < maxAmp[AMP2]) app->render->camera.x = maxAmp[AMP2];
		else if (lvlAmp == AMP1 && app->render->camera.x < maxAmp[AMP1]) app->render->camera.x = maxAmp[AMP1];
		else if (lvlAmp == AMP0 && app->render->camera.x < maxAmp[AMP0]) app->render->camera.x = maxAmp[AMP0];
	}
}

void SceneEditor::DebugMargin(bool debug)
{
	if (debug)
	{
		app->render->DrawLine(W_MARGIN, H_MARGIN, WIN_WIDTH + W_MARGIN, H_MARGIN, { 255, 255, 255, 100 }, false);
		app->render->DrawLine(W_MARGIN, H_MARGIN, W_MARGIN, WIN_HEIGHT + H_MARGIN, { 255, 255, 255, 100 }, false);
		app->render->DrawLine(W_MARGIN, WIN_HEIGHT + H_MARGIN, WIN_WIDTH + W_MARGIN, WIN_HEIGHT + H_MARGIN, { 255, 255, 255, 80 }, false);
		app->render->DrawLine(WIN_WIDTH + W_MARGIN + 1, H_MARGIN, WIN_WIDTH + W_MARGIN + 1, WIN_HEIGHT + H_MARGIN, { 255, 255, 255, 80 }, false);
	}
}