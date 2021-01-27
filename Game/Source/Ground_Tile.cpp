#include "App.h"
#include "Render.h"
#include "Scene.h"
#include "Scene_Editor.h"
#include "Textures.h"
#include "Ground_Tile.h"

GroundTile::GroundTile()
{

}

GroundTile::GroundTile(iPoint pos, iPoint coords)
{
	groundTex = app->tex->Load("Assets/Tilesets/ground_tileset.png");
	position = pos;
	coordinates = coords;
	groundRect = {pos.x, pos.y, 41, 41};
}

GroundTile::~GroundTile()
{
	app->tex->UnLoad(groundTex);
}

void GroundTile::Draw()
{
	iPoint upTile = { coordinates.x, coordinates.y - 1 };
	iPoint downTile = { coordinates.x, coordinates.y + 1 };
	iPoint leftTile = { coordinates.x - 1, coordinates.y };
	iPoint rightTile = { coordinates.x + 1, coordinates.y };

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	ListItem<GroundTile*>* list;
	for (list = app->scene->sceneEditor->groundTiles.start; list != nullptr; list = list->next)
	{
		if (list->data->coordinates == upTile) up = true;
		if (list->data->coordinates == downTile) down = true;
		if (list->data->coordinates == leftTile) left = true;
		if (list->data->coordinates == rightTile) right = true;

		if (up && down && left && right) break;
	}

	if (!up && left && !down && !right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground4);
	}
	else if (up && !left && !down && !right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground4, 1.0f, 90);
	}
	else if (!up && !left && down && !right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground4, 1.0f, -90);
	}
	else if (!up && !left && !down && right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground4, 1.0f, 180);
	}
	else if (!up && left && down && !right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground3);
	}
	else if (up && left && !down && !right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground3, 1.0f, 90);
	}
	else if (up && !left && !down && right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground3, 1.0f, 180);
	}
	else if (!up && !left && down && right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground3, 1.0f, -90);
	}
	else if (!up && left && down && right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground1);
	}
	else if (up && !left && down && right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground1, 1.0f, -90);
	}
	else if (up && left && !down && right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground1, 1.0f, 180);
	}
	else if (up && left && down && !right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground1, 1.0f, 90);
	}
	else if (up & left & down & right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground2);
	}
	else if (!up & left & !down & right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground6);
	}
	else if (up & !left & down & !right)
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground6, 1.0f, 90);
	}
	else
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground5);
	}
}
