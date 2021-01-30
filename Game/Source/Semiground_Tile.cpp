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
	semigroundHRect.x = pos.x;
	semigroundHRect.y = pos.y;
	semigroundVRect.x += pos.x;
	semigroundVRect.y = pos.y;

	if (!rot) semigroundRect = semigroundHRect;
	else if (rot) semigroundRect = semigroundVRect;
	semigroundRectA = semigroundVRect;

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
	bool upBoth = false;
	bool downBoth = false;
	bool leftBoth = false;
	bool rightBoth = false;
	bool bothT = false;

	ListItem<SemigroundTile*>* list;
	for (list = app->scene->sceneEditor->semigroundTiles.start; list != nullptr; list = list->next)
	{
		if (list->data->coordinates == upTile)
		{
			up = true;
			if (list->data->rotated) upRot = true;
			if (list->data->both) upBoth = true;
		}
		if (list->data->coordinates == downTile)
		{
			down = true;
			if (list->data->rotated) downRot = true;
			if (list->data->both) downBoth = true;
		}
		if (list->data->coordinates == leftTile)
		{
			left = true;
			if (list->data->rotated) leftRot = true;
			if (list->data->both) leftBoth = true;
		}
		if (list->data->coordinates == rightTile)
		{
			right = true;
			if (list->data->rotated) rightRot = true;
			if (list->data->both) rightBoth = true;
		}

		if (up && left && down && right) break;
	}

	if (left && !leftRot && !leftBoth && down && downRot)
	{
		bothT = true;
		rotated = false;
		semigroundRect = semigroundHRect;
	}

	both = bothT;

	if (!both)
	{
		if (!rotated)
		{
			if (!left && !right)
			{
				app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1);
			}
			else if (left && right)
			{
				if (!leftRot && !rightRot)
				{
					if (!leftBoth) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground2);
					else if (leftBoth) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground5);
				}
				else if (!leftRot && rightRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground4);
				else if (leftRot && !rightRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground5);
				else if (leftRot && rightRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1);
			}
			else if (!left && right)
			{
				if (!rightRot)
				{
					app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground5);
				}
				else if (rightRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1);
			}
			else if (left && !right)
			{
				if (!leftRot)
				{
					if (!leftBoth) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground4);
					else if (leftBoth) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1);
				}
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
				else if (!upRot && downRot)
				{
					if (!upBoth) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground5, 1.0f, 90);
					else if (upBoth) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground2, 1.0f, 90);
				}
				else if (!upRot && !downRot)
				{
					if (!upBoth) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1, 1.0f, 90);
					else if (upBoth) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground4, 1.0f, 90);
				}
			}
			else if (!up && down)
			{
				if (downRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground5, 1.0f, 90);
				else if (!downRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1, 1.0f, 90);
			}
			else if (up && !down)
			{
				if (upRot) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground4, 1.0f, 90);
				else if (!upRot)
				{
					if (!upBoth) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground1, 1.0f, 90);
					else if (upBoth) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground4, 1.0f, 90);
				}
			}
		}
	}
	else if (both) app->render->DrawTexture(semigroundTex, position.x, position.y, &semiground3);
}