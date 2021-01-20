#include "App.h"
#include "Scene_Editor.h"
#include "Render.h"
#include "Input.h"
#include "Textures.h"
#include "Window.h"

#include "Log.h"

SceneEditor::SceneEditor()
{

}

SceneEditor::SceneEditor(LevelAmplitude lvl)
{

	lvlAmp = lvl;

	for (int x = 0; x < 25; x++)
	{
		for (int y = 0; y < 26; y++)
		{
			Tileset0.Add(new uTile({ TILE_SIZE * x + W_MARGIN, TILE_SIZE * y + H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2, 41, 41 }, { x, y }));
		}
	}
}

SceneEditor::~SceneEditor()
{
}

void SceneEditor::Draw()
{
	app->render->DrawTexture(background, W_MARGIN, H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2);

	DebugTileset(AMP0, debugTileset);

	DrawGrid();
}

void SceneEditor::CleanUp()
{
	if (background != nullptr)
		app->tex->UnLoad(background);
}

void SceneEditor::DrawGrid()
{
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

	DebugMargin(debugMargin);
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
		app->render->DrawLine(W_MARGIN, H_MARGIN, WIN_WIDTH + W_MARGIN, H_MARGIN, { 0, 0, 0, 200 }, false);
		app->render->DrawLine(W_MARGIN, H_MARGIN, W_MARGIN, WIN_HEIGHT + H_MARGIN, { 0, 0, 0, 200 }, false);
		app->render->DrawLine(W_MARGIN, WIN_HEIGHT + H_MARGIN, WIN_WIDTH + W_MARGIN, WIN_HEIGHT + H_MARGIN, { 0, 0, 0, 200 }, false);
		app->render->DrawLine(WIN_WIDTH + W_MARGIN, H_MARGIN, WIN_WIDTH + W_MARGIN + 1, WIN_HEIGHT + H_MARGIN, { 0, 0, 0, 200 }, false);
	}
}

void SceneEditor::DebugTileset(LevelAmplitude lvlAmp, bool debug)
{
	if (debug)
	{
		iPoint mousePos = GetMousePosInTile();

		if (lvlAmp == AMP0)
		{
			ListItem<uTile*>* list;
			for (list = Tileset0.start; list != nullptr; list = list->next)
			{
				if (list->data == GetTileFromXY(mousePos.x, mousePos.y))
				{
					app->render->DrawRectangle(list->data->tileRect, { 200, 255, 100, 200 });
				}
				else
				{
					app->render->DrawRectangle(list->data->tileRect, { 255, 200, 100, 200 });
				}
			}
		}
	}
}

uTile* SceneEditor::GetTileFromXY(int x, int y)
{
	int floorX = floor(x / TILE_SIZE);
	int floorY = floor(y / TILE_SIZE);

	ListItem<uTile*>* list;
	for (list = Tileset0.start; list != nullptr; list = list->next)
	{
		if (list->data->position.x == floorX && list->data->position.y == floorY)
		{
			return list->data;
		}
	}
	return nullptr;
}

iPoint SceneEditor::GetMousePosInTile()
{
	iPoint pos;
	app->input->GetMousePosition(pos.x, pos.y);
	pos.x -= W_MARGIN;
	pos.y += (WIN_HEIGHT - H_MARGIN - TILE_SIZE * 2);

	pos.x -= app->render->camera.x;
	pos.y -= app->render->camera.y;

	return pos;
}

uTile::uTile(SDL_Rect r, iPoint pos)
{
	tileRect = r;
	position = pos;
}
