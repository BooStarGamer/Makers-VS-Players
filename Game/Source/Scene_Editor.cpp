#include "App.h"
#include "Scene.h"
#include "Scene_Editor.h"
#include "Player.h"
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
			Tileset0.Add(new DebugTile({ TILE_SIZE * x + W_MARGIN, TILE_SIZE * y + H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2, 41, 41 }, { x, y }));
			Tileset1.Add(new DebugTile({ TILE_SIZE * x + W_MARGIN + WIN_WIDTH * 1, TILE_SIZE * y + H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2, 41, 41 }, { x + 25, y }));
			Tileset2.Add(new DebugTile({ TILE_SIZE * x + W_MARGIN + WIN_WIDTH * 2, TILE_SIZE * y + H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2, 41, 41 }, { x + 50, y }));
			Tileset3.Add(new DebugTile({ TILE_SIZE * x + W_MARGIN + WIN_WIDTH * 3, TILE_SIZE * y + H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2, 41, 41 }, { x + 75, y }));
		}
	}
}

SceneEditor::~SceneEditor()
{
}

void SceneEditor::Draw()
{
	app->render->DrawTexture(background, W_MARGIN, H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2);

	if (editMode) DebugTileset(lvlAmp, debugTileset);

	DrawTiles();

	//DEBUG CAM LOGIC Y (Glitch: Put player on max top)
	/*if (!editMode)
	{
		app->render->DrawLine(W_MARGIN, YCamHigh, W_MARGIN + WIN_WIDTH, YCamHigh, { 100, 255, 255, 255 });
	}
	if (!editMode)
	{
		app->render->DrawLine(W_MARGIN, YCamLow, W_MARGIN + WIN_WIDTH, YCamLow, { 100, 255, 255, 255 });
	}*/

	//DEBUG CAM LOGIC X (Glitch: Put player out of XCamBack/XCamFor)
	/*if (!editMode)
	{
		app->render->DrawLine(XCamFor, UP_MAXIMUM, XCamFor, WIN_HEIGHT + H_MARGIN, { 100, 255, 255, 255 });
	}
	if (!editMode)
	{
		app->render->DrawLine(XCamBack, UP_MAXIMUM, XCamBack, WIN_HEIGHT + H_MARGIN, { 100, 255, 255, 255 });
	}*/

	if (editMode) DrawGrid();
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

void SceneEditor::DragPlayerLogic()
{
	if (editMode)
	{
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && IsMouseInPlayer())
		{
			deltaPos = GetMousePosInPlayer();
		}
		else if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT && IsMouseInPlayer())
		{
			selectedTile = NO_TILE;
			iPoint pos = GetMousePosInTile();
			pos.y += UP_MAXIMUM;
			if (pos.x - deltaPos.x > 0 && pos.y + (app->scene->player->collider.h - deltaPos.y) < WIN_HEIGHT + H_MARGIN)
			{
				pos.x += W_MARGIN;
				pos -= deltaPos;
				DragPlayer(pos);
			}
		}
	}
}

void SceneEditor::CameraMoveLogic()
{
	if (editMode)
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
	}
	else
	{
		if (app->scene->player->position.y + app->scene->player->collider.h < (540 - H_MARGIN) && 
			app->scene->player->position.y > (UP_MAXIMUM + 180))
		{
			int pos = app->scene->player->position.y;
			int size = app->scene->player->collider.h;

			if (pos < YCamHigh)
			{
				YCamHigh = pos;
				YCamLow = YCamHigh + 360;
				app->render->camera.y = -1 * (YCamHigh - 180);
			}
			else if ((pos + size) > YCamLow)
			{
				YCamLow = pos + size;
				YCamHigh = YCamLow - 360;
				app->render->camera.y = -1 * (YCamHigh - 180);
			}
		}

		if (app->scene->player->position.x + app->scene->player->collider.w < -maxAmp[lvlAmp] + W_MARGIN * 2 + WIN_WIDTH - (320 + 320 / 2) &&
			app->scene->player->position.x > (320 + 320 / 2 + W_MARGIN))
		{
			int pos = app->scene->player->position.x;
			int size = app->scene->player->collider.w;

			if (pos < XCamBack)
			{
				XCamBack = pos;
				XCamFor = XCamBack + CamForBackDif;
				app->render->camera.x = -1 * (XCamBack - (320 + 320 / 2));
			}
			else if ((pos + size) > XCamFor)
			{
				XCamFor = pos + size;
				XCamBack = XCamFor - CamForBackDif;
				app->render->camera.x = -1 * (XCamBack - (320 + 320 / 2));
			}
		}

	}
}

void SceneEditor::LevelAmpLogic()
{
	if (editMode)
	{
		if (app->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN)
		{
			if (lvlAmp != AMP3) lvlAmp = (LevelAmplitude)((int)lvlAmp + 1);
		}

		if (app->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN)
		{
			//CHANGE lvlAmp VARIABLE
			if (lvlAmp != AMP0) lvlAmp = (LevelAmplitude)((int)lvlAmp - 1);
			
			//MOVE CAMERA
			if (lvlAmp == AMP2 && app->render->camera.x < maxAmp[AMP2]) app->render->camera.x = maxAmp[AMP2];
			else if (lvlAmp == AMP1 && app->render->camera.x < maxAmp[AMP1]) app->render->camera.x = maxAmp[AMP1];
			else if (lvlAmp == AMP0 && app->render->camera.x < maxAmp[AMP0]) app->render->camera.x = maxAmp[AMP0];

			//ERASE BLOCKS IN OTHER AMPLITUDES
			EraseAllTileset(GROUND, lvlAmp);
		}
	}
}

void SceneEditor::PlaceTileLogic()
{
	if (editMode)
	{
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			iPoint coords = GetMouseCoordInTile();
			iPoint pos = GetPosFromCoords(coords);

			if (pos.x >= 128 && pos.y <= 606 && pos.y >= H_MARGIN - 40 - app->render->camera.y &&
				pos.x <= WIN_WIDTH + W_MARGIN - app->render->camera.x) //40 for almost 1 tile
			{
				PlaceTile(selectedTile, pos, coords);
			}
		}
	}
}

void SceneEditor::EraseTileLogic()
{
	if (editMode)
	{
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			iPoint coords = GetMouseCoordInTile();
			iPoint pos = GetPosFromCoords(coords);

			if (pos.x >= 128 && pos.y <= 606 && pos.y >= H_MARGIN - 40 - app->render->camera.y &&
				pos.x <= WIN_WIDTH + W_MARGIN - app->render->camera.x) //40 for almost 1 tile
			{
				EraseTile(selectedTile, coords);
			}
		}
	}
}

void SceneEditor::TileSelectedLogic()
{
	if (editMode)
	{
		if (app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) selectedTile = NO_TILE;
		if (app->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN) selectedTile = ERASE;
		else if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) selectedTile = GROUND;
	}
}

void SceneEditor::EditModeLogic()
{
	editMode = !editMode;

	if (!editMode)
	{
		app->render->camera.y += H_MARGIN;
		app->render->camera.x -= W_MARGIN;
		YCamHigh = -app->render->camera.y + 180;
		YCamLow = -app->render->camera.y + 540;
		XCamFor = -app->render->camera.x + 960 - 320 / 2;
		XCamBack = -app->render->camera.x + 320 + 320 / 2;
	}
	else if (editMode)
	{
		app->render->camera.y -= H_MARGIN;
		app->render->camera.x += W_MARGIN;
	}
}

void SceneEditor::ReplacePlayerLogic()
{
	if (!editMode)
	{
		if (app->scene->player->collider.y > 720)
		{
			EditModeLogic();
			app->scene->player->collider.y -= 400;
		}
	}
}

void SceneEditor::PlaceTile(TileType type, iPoint pos, iPoint coords)
{
	bool existent = false;

	if (type == GROUND)
	{
		ListItem<GroundTile*>* list;
		for (list = groundTiles.start; list != nullptr; list = list->next)
		{
			if (list->data->GetCoords() == coords)
			{
				existent = true;
				break;
			}
		}

		if (!existent) groundTiles.Add(new GroundTile(pos, coords));
	}
}

void SceneEditor::DragPlayer(iPoint pos)
{
	app->scene->player->collider.x = pos.x;
	app->scene->player->collider.y = pos.y;
	app->scene->player->UpdatePlayerPos();
}

void SceneEditor::EraseTile(TileType type, iPoint coords)
{
	if (type == ERASE)
	{
		ListItem<GroundTile*>* list;
		for (list = groundTiles.start; list != nullptr; list = list->next)
		{
			if (list->data->GetCoords() == coords)
			{
				delete list->data;
				groundTiles.Del(list);
				list->data = nullptr;
				break;
			}
		}
	}
}

void SceneEditor::EraseAllTileset(TileType type, LevelAmplitude lvlAmp)
{
	int sum = {};
	if (lvlAmp == AMP0) sum = 25;
	else if (lvlAmp == AMP1) sum = 50;
	else if (lvlAmp == AMP2) sum = 75;

	if (type == GROUND)
	{
		for (int x = sum; x < 25 + sum; x++)
		{
			for (int y = 0; y < 26; y++)
			{
				ListItem<GroundTile*>* toErase = GetGroundTileFromXY(iPoint(x, y));
				if (toErase != nullptr)
				{
					delete toErase->data;
					groundTiles.Del(toErase);
					toErase->data = nullptr;
				}
			}
		}
	}
}

// DEBUG FUNCTIONS

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
			ListItem<DebugTile*>* list0;
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
			ListItem<DebugTile*>* list0;
			for (list0 = Tileset0.start; list0 != nullptr; list0 = list0->next)
			{
				app->render->DrawRectangle(list0->data->tileRect, { 255, 200, 100, alpha });
			}
		}
		
		if ((int)lvlAmp > 0 && mousePos.x >= -maxAmp[1] && mousePos.x < -maxAmp[2])
		{
			ListItem<DebugTile*>* list1;
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
			ListItem<DebugTile*>* list1;
			for (list1 = Tileset1.start; list1 != nullptr; list1 = list1->next)
			{
				app->render->DrawRectangle(list1->data->tileRect, { 255, 200, 100, alpha });
			}
		}

		if ((int)lvlAmp > 1 && mousePos.x >= -maxAmp[2] && mousePos.x < -maxAmp[3])
		{
			ListItem<DebugTile*>* list2;
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
			ListItem<DebugTile*>* list2;
			for (list2 = Tileset2.start; list2 != nullptr; list2 = list2->next)
			{
				app->render->DrawRectangle(list2->data->tileRect, { 255, 200, 100, alpha });
			}
		}

		if ((int)lvlAmp > 2 && mousePos.x >= -maxAmp[3] && mousePos.x < -maxAmp[3] + WIN_WIDTH)
		{
			ListItem<DebugTile*>* list3;
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
			ListItem<DebugTile*>* list3;
			for (list3 = Tileset3.start; list3 != nullptr; list3 = list3->next)
			{
				app->render->DrawRectangle(list3->data->tileRect, { 255, 200, 100, alpha });
			}
		}
	}
}

void SceneEditor::DrawTiles()
{
	ListItem<GroundTile*>* list;
	for (list = groundTiles.start; list != nullptr; list = list->next)
	{
		list->data->Draw();
	}
}

// ADDITIONAL FUNCTIONS

DebugTile* SceneEditor::GetTileFromXY(int x, int y, LevelAmplitude lvlAmp)
{
	int floorX = floor(x / TILE_SIZE);
	int floorY = floor(y / TILE_SIZE);

	if ((int)lvlAmp >= 0)
	{
		ListItem<DebugTile*>* list0;
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
		ListItem<DebugTile*>* list1;
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
		ListItem<DebugTile*>* list2;
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
		ListItem<DebugTile*>* list3;
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

ListItem<GroundTile*>* SceneEditor::GetGroundTileFromXY(iPoint coords)
{
	ListItem<GroundTile*>* list;
	for (list = groundTiles.start; list != nullptr; list = list->next)
	{
		if (list->data->GetCoords() == coords)
		{
			return list;
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

iPoint SceneEditor::GetPosFromCoords(iPoint coords)
{
	coords.x = (coords.x * TILE_SIZE) + W_MARGIN;
	coords.y = (coords.y * TILE_SIZE) + H_MARGIN - WIN_HEIGHT + TILE_SIZE * 2;

	return coords;
}

iPoint SceneEditor::GetMouseCoordInTile()
{
	iPoint pos;
	app->input->GetMousePosition(pos.x, pos.y);
	pos.x -= W_MARGIN;
	pos.y += (WIN_HEIGHT - H_MARGIN - TILE_SIZE * 2);

	pos.x -= app->render->camera.x;
	pos.y -= app->render->camera.y;

	if (pos.x < 0) pos.x = floor(pos.x / TILE_SIZE) - 1;
	else pos.x = floor(pos.x / TILE_SIZE);

	if (pos.y < 0) pos.y = floor(pos.y / TILE_SIZE) - 1;
	else pos.y = floor(pos.y / TILE_SIZE);

	return pos;
}

iPoint SceneEditor::GetMousePosInPlayer()
{
	if (IsMouseInPlayer())
	{
		iPoint pos = GetMousePosInTile();
		pos.y += UP_MAXIMUM;
		pos.x += W_MARGIN;

		return iPoint(pos.x - app->scene->player->collider.x, pos.y - app->scene->player->collider.y);
	}

	return iPoint();
}

DebugTile::DebugTile(SDL_Rect r, iPoint pos)
{
	tileRect = r;
	position = pos;
}

bool SceneEditor::IsMouseInPlayer()
{
	iPoint pos = GetMousePosInTile();
	pos.y += UP_MAXIMUM;
	pos.x += W_MARGIN;

	if (pos.x > app->scene->player->collider.x &&
		pos.x < app->scene->player->collider.x + app->scene->player->collider.w &&
		pos.y > app->scene->player->collider.y &&
		pos.y < app->scene->player->collider.y + app->scene->player->collider.h) return true;

	return false;
}
