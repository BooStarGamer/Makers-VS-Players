#include "App.h"
#include "Render.h"
#include "Scene.h"
#include "Scene_Editor.h"
#include "Textures.h"
#include "Semiground_Tile.h"

SemigroundTile::SemigroundTile()
{

}

SemigroundTile::SemigroundTile(iPoint pos, iPoint coords, bool rot)
{
	semigroundTex = app->tex->Load("Assets/Tilesets/semiground_tileset.png");
	position = pos;
	coordinates = coords;
	semigroundHRect = { pos.x, pos.y, 41, 4 };
	semigroundVLRect = { pos.x, pos.y, 4, 41 };
	semigroundVRRect = { pos.x + 37, pos.y, 4, 41 };
	rotated = rot;
}

SemigroundTile::~SemigroundTile()
{
	app->tex->UnLoad(semigroundTex);
}

void SemigroundTile::Draw()
{
	iPoint upTile = { coordinates.x, coordinates.y - 1 };
	iPoint downTile = { coordinates.x, coordinates.y + 1 };
	iPoint leftTile = { coordinates.x - 1, coordinates.y };
	iPoint rightTile = { coordinates.x + 1, coordinates.y };

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool upRot = false;
	bool downRot = false;
	bool leftRot = false;
	bool rightRot = false;

	ListItem<SemigroundTile*>* list;
	for (list = app->scene->sceneEditor->semigroundTiles.start; list != nullptr; list = list->next)
	{
		if (list->data->coordinates == upTile)
		{
			up = true;
			if (list->data->rotated) upRot = true;
		}
		if (list->data->coordinates == downTile)
		{
			down = true;
			if (list->data->rotated) downRot = true;
		}
		if (list->data->coordinates == leftTile)
		{
			left = true;
			if (list->data->rotated) leftRot = true;
		}
		if (list->data->coordinates == rightTile)
		{
			right = true;
			if (list->data->rotated) rightRot = true;
		}

		if (up && left && down && right) break;
	}

	if (!rotated)
	{
		if (!left && !right)
		{
			app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1);
		}
		else if (left && right)
		{
			if (!leftRot && !rightRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground2);
			else if (!leftRot && rightRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground4);
			else if (leftRot && !rightRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground5);
			else if (leftRot && rightRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1);
		}
		else if (!left && right)
		{
			if (!rightRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground5);
			else if (rightRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1);
		}
		else if (left && !right)
		{
			if (!leftRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground4);
			else if (leftRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1);
		}
	}
	else if (rotated)
	{
		if (!up && !down)
		{
			app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1, 1.0f, 90);
		}
		else if (up && down)
		{
			if (upRot && downRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground2, 1.0f, 90);
			else if (upRot && !downRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground4, 1.0f, 90);
			else if (!upRot && downRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground5, 1.0f, 90);
			else if (!upRot && !downRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1, 1.0f, 90);
		}
		else if (!up && down)
		{
			if (downRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground5, 1.0f, 90);
			else if (!downRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1, 1.0f, 90);
		}
		else if (up && !down)
		{
			if (upRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground4, 1.0f, 90);
			else if (!upRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1, 1.0f, 90);
		}
	}
}