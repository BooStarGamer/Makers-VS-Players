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
	iPoint upLTile = { coordinates.x - 1, coordinates.y - 1 };
	iPoint downLTile = { coordinates.x - 1, coordinates.y + 1 };
	iPoint upRTile = { coordinates.x + 1, coordinates.y - 1};
	iPoint downRTile = { coordinates.x + 1, coordinates.y + 1};

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool upL = false;
	bool downL = false;
	bool upR = false;
	bool downR = false;

	ListItem<GroundTile*>* list;
	for (list = app->scene->sceneEditor->groundTiles.start; list != nullptr; list = list->next)
	{
		if (list->data->coordinates == upTile) up = true;
		if (list->data->coordinates == downTile) down = true;
		if (list->data->coordinates == leftTile) left = true;
		if (list->data->coordinates == rightTile) right = true;
		if (list->data->coordinates == upLTile) upL = true;
		if (list->data->coordinates == downLTile) downL = true;
		if (list->data->coordinates == upRTile) upR = true;
		if (list->data->coordinates == downRTile) downR = true;

		if (up && down && left && right && upL && downL && upR && downR) break;
	}

	if (!up && left && !down && !right) //No Diagonal
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground4);
	}
	else if (up && !left && !down && !right) //No Diagonal
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground4, 1.0f, 90);
	}
	else if (!up && !left && down && !right) //No Diagonal
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground4, 1.0f, -90);
	}
	else if (!up && !left && !down && right) //No Diagonal
	{
		app->render->DrawTexture(groundTex, position.x, position.y, &ground4, 1.0f, 180);
	}
	else if (!up && left && down && !right) //Diagonal DownL
	{
		if (downL) app->render->DrawTexture(groundTex, position.x, position.y, &ground3);
		else if (!downL) app->render->DrawTexture(groundTex, position.x, position.y, &ground12, 1.0f, -90);
	}
	else if (up && left && !down && !right) //Diagonal UpL
	{
		if (upL) app->render->DrawTexture(groundTex, position.x, position.y, &ground3, 1.0f, 90);
		else if (!upL) app->render->DrawTexture(groundTex, position.x, position.y, &ground12);
	}
	else if (up && !left && !down && right) //Diagonal UpR
	{
		if (upR) app->render->DrawTexture(groundTex, position.x, position.y, &ground3, 1.0f, 180);
		else if (!upR) app->render->DrawTexture(groundTex, position.x, position.y, &ground12, 1.0f, 90);
	}
	else if (!up && !left && down && right) //Diagonal DownR
	{
		if (downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground3, 1.0f, -90);
		else if (!downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground12, 1.0f, 180);
	}
	else if (!up && left && down && right) //Diagonal DownL, DownR, Both
	{
		if (downL && downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground1);
		else if (downL && !downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground9, 1.0f, 180);
		else if (!downL && downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground10, 1.0f, 180);
		else if (!downL && !downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground11, 1.0f, 180);
	}
	else if (up && !left && down && right) //Diagonal UpR, DownR, Both
	{
		if (upR && downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground1, 1.0f, -90);
		else if (upR && !downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground10, 1.0f, 90);
		else if (!upR && downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground9, 1.0f, 90);
		else if (!upR && !downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground11, 1.0f, 90);
	}
	else if (up && left && !down && right) //Diagonal UpL, UpR, Both
	{
		if (upL && upR) app->render->DrawTexture(groundTex, position.x, position.y, &ground1, 1.0f, 180);
		else if (upL && !upR) app->render->DrawTexture(groundTex, position.x, position.y, &ground10);
		else if (!upL && upR) app->render->DrawTexture(groundTex, position.x, position.y, &ground9);
		else if (!upL && !upR) app->render->DrawTexture(groundTex, position.x, position.y, &ground11);
	}
	else if (up && left && down && !right) //Diagonal UpL, DownL, Both
	{
		if (upL && downL) app->render->DrawTexture(groundTex, position.x, position.y, &ground1, 1.0f, 90);
		else if (upL && !downL) app->render->DrawTexture(groundTex, position.x, position.y, &ground9, 1.0f, -90);
		else if (!upL && downL) app->render->DrawTexture(groundTex, position.x, position.y, &ground10, 1.0f, -90);
		else if (!upL && !downL) app->render->DrawTexture(groundTex, position.x, position.y, &ground11, 1.0f, -90);
	}
	else if (up & left & down & right)
	{
		if (upL && upR && downL && downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground2);
		else if (!upL && upR && downL && downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground7);
		else if (upL && !upR && downL && downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground7, 1.0f, 90);
		else if (upL && upR && !downL && downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground7, 1.0f, -90);
		else if (upL && upR && downL && !downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground7, 1.0f, 180);
		else if (!upL && !upR && !downL && downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground13);
		else if (upL && !upR && !downL && !downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground13, 1.0f, 180);
		else if (!upL && upR && !downL && !downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground13, 1.0f, -90);
		else if (!upL && !upR && downL && !downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground13, 1.0f, 90);
		else if (upL && !upR && !downL && downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground15, 1.0f, 90);
		else if (!upL && upR && downL && !downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground15);
		else if (!upL && !upR && downL && downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground8);
		else if (upL && upR && !downL && !downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground8, 1.0f, 180);
		else if (!upL && upR && !downL && downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground8, 1.0f, -90);
		else if (upL && !upR && downL && !downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground8, 1.0f, 90);
		else if (!upL && !upR && !downL && !downR) app->render->DrawTexture(groundTex, position.x, position.y, &ground14);

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
