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
			Tileset0.Add(new debugTile({ TILE_SIZE * x + W_MARGIN, TILE_SIZE * y + H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2, 41, 41 }, { x, y }));
			Tileset1.Add(new debugTile({ TILE_SIZE * x + W_MARGIN + WIN_WIDTH * 1, TILE_SIZE * y + H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2, 41, 41 }, { x + 25, y }));
			Tileset2.Add(new debugTile({ TILE_SIZE * x + W_MARGIN + WIN_WIDTH * 2, TILE_SIZE * y + H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2, 41, 41 }, { x + 50, y }));
			Tileset3.Add(new debugTile({ TILE_SIZE * x + W_MARGIN + WIN_WIDTH * 3, TILE_SIZE * y + H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2, 41, 41 }, { x + 75, y }));
		}
	}
}

SceneEditor::~SceneEditor()
{
}

void SceneEditor::Draw()
{
	app->render->DrawTexture(background, W_MARGIN, H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2);

	DebugTileset(lvlAmp, debugTileset);

	DrawTiles();

	DrawGrid();
}

void SceneEditor::CleanUp()
{
	if (background != nullptr)
		app->tex->UnLoad(background);
}

// SCENE EDITION FUNCTIONS

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

void SceneEditor::CameraMoveLogic()
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

void SceneEditor::PlaceTileLogic()
{
	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		iPoint pos = GetMouseCoordInTile();

		PlaceTile(selectedTile, pos.x, pos.y);
	}
}

void SceneEditor::PlaceTile(TileType type, int x, int y)
{
	//if (type == GROUND)
	//{
		groundTiles.Add(new GroundTile(x * TILE_SIZE + 5, y * TILE_SIZE - 8));
	//}
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
	Uint8 alpha = 100;
	if (debug)
	{
		iPoint mousePos = GetMousePosInTile();

		if ((int)lvlAmp >= 0 && mousePos.x >= 0 && mousePos.x < -maxAmp[1])
		{
			ListItem<debugTile*>* list0;
			for (list0 = Tileset0.start; list0 != nullptr; list0 = list0->next)
			{
				if (list0->data == GetTileFromXY(mousePos.x, mousePos.y, lvlAmp))
				{
					app->render->DrawRectangle(list0->data->tileRect, { 200, 255, 100, alpha });
				}
				else
				{
					app->render->DrawRectangle(list0->data->tileRect, { 255, 200, 100, alpha });
				}
			}
		}
		else if ((int)lvlAmp >= 0)
		{
			ListItem<debugTile*>* list0;
			for (list0 = Tileset0.start; list0 != nullptr; list0 = list0->next)
			{
				app->render->DrawRectangle(list0->data->tileRect, { 255, 200, 100, alpha });
			}
		}
		
		if ((int)lvlAmp > 0 && mousePos.x >= -maxAmp[1] && mousePos.x < -maxAmp[2])
		{
			ListItem<debugTile*>* list1;
			for (list1 = Tileset1.start; list1 != nullptr; list1 = list1->next)
			{
				if (list1->data == GetTileFromXY(mousePos.x, mousePos.y, lvlAmp))
				{
					app->render->DrawRectangle(list1->data->tileRect, { 200, 255, 100, alpha });
				}
				else
				{
					app->render->DrawRectangle(list1->data->tileRect, { 255, 200, 100, alpha });
				}
			}
		}
		else if ((int)lvlAmp > 0)
		{
			ListItem<debugTile*>* list1;
			for (list1 = Tileset1.start; list1 != nullptr; list1 = list1->next)
			{
				app->render->DrawRectangle(list1->data->tileRect, { 255, 200, 100, alpha });
			}
		}

		if ((int)lvlAmp > 1 && mousePos.x >= -maxAmp[2] && mousePos.x < -maxAmp[3])
		{
			ListItem<debugTile*>* list2;
			for (list2 = Tileset2.start; list2 != nullptr; list2 = list2->next)
			{
				if (list2->data == GetTileFromXY(mousePos.x, mousePos.y, lvlAmp))
				{
					app->render->DrawRectangle(list2->data->tileRect, { 200, 255, 100, alpha });
				}
				else
				{
					app->render->DrawRectangle(list2->data->tileRect, { 255, 200, 100, alpha });
				}
			}
		}
		else if ((int)lvlAmp > 1)
		{
			ListItem<debugTile*>* list2;
			for (list2 = Tileset2.start; list2 != nullptr; list2 = list2->next)
			{
				app->render->DrawRectangle(list2->data->tileRect, { 255, 200, 100, alpha });
			}
		}

		if ((int)lvlAmp > 2 && mousePos.x >= -maxAmp[3] && mousePos.x < -maxAmp[3] + WIN_WIDTH)
		{
			ListItem<debugTile*>* list3;
			for (list3 = Tileset3.start; list3 != nullptr; list3 = list3->next)
			{
				if (list3->data == GetTileFromXY(mousePos.x, mousePos.y, lvlAmp))
				{
					app->render->DrawRectangle(list3->data->tileRect, { 200, 255, 100, alpha });
				}
				else
				{
					app->render->DrawRectangle(list3->data->tileRect, { 255, 200, 100, alpha });
				}
			}
		}
		else if ((int)lvlAmp > 2)
		{
			ListItem<debugTile*>* list3;
			for (list3 = Tileset3.start; list3 != nullptr; list3 = list3->next)
			{
				app->render->DrawRectangle(list3->data->tileRect, { 255, 200, 100, alpha });
			}
		}
	}
}

// ADDITIONAL FUNCTIONS

debugTile* SceneEditor::GetTileFromXY(int x, int y, LevelAmplitude lvlAmp)
{
	int floorX = floor(x / TILE_SIZE);
	int floorY = floor(y / TILE_SIZE);

	if ((int)lvlAmp >= 0)
	{
		ListItem<debugTile*>* list0;
		for (list0 = Tileset0.start; list0 != nullptr; list0 = list0->next)
		{
			if (list0->data->position.x == floorX && list0->data->position.y == floorY)
			{
				return list0->data;
			}
		}
	}

	if ((int)lvlAmp > 0)
	{
		ListItem<debugTile*>* list1;
		for (list1 = Tileset1.start; list1 != nullptr; list1 = list1->next)
		{
			if (list1->data->position.x == floorX && list1->data->position.y == floorY)
			{
				return list1->data;
			}
		}
	}

	if ((int)lvlAmp > 1)
	{
		ListItem<debugTile*>* list2;
		for (list2 = Tileset2.start; list2 != nullptr; list2 = list2->next)
		{
			if (list2->data->position.x == floorX && list2->data->position.y == floorY)
			{
				return list2->data;
			}
		}
	}

	if ((int)lvlAmp > 2)
	{
		ListItem<debugTile*>* list3;
		for (list3 = Tileset3.start; list3 != nullptr; list3 = list3->next)
		{
			if (list3->data->position.x == floorX && list3->data->position.y == floorY)
			{
				return list3->data;
			}
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

iPoint SceneEditor::GetMouseCoordInTile()
{
	iPoint pos;
	app->input->GetMousePosition(pos.x, pos.y);
	//pos.x -= W_MARGIN;
	//pos.y += (WIN_HEIGHT - H_MARGIN - TILE_SIZE * 2);

	//pos.x -= app->render->camera.x;
	//pos.y -= app->render->camera.y;

	pos.x = floor(pos.x / TILE_SIZE);
	pos.y = floor(pos.y / TILE_SIZE);

	return pos;
}

void SceneEditor::DrawTiles()
{
	ListItem<GroundTile*>* list;
	for (list = groundTiles.start; list != nullptr; list = list->next)
	{
		list->data->Draw();
	}
}

debugTile::debugTile(SDL_Rect r, iPoint pos)
{
	tileRect = r;
	position = pos;
}
