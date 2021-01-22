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
}

void GroundTile::Draw()
{
	iPoint upTile = { coordinates.x, coordinates.y - 1 };
	ListItem<GroundTile*>* list;
	for (list = app->scene->sceneEditor->groundTiles.start; list != nullptr; list = list->next)
	{
		if (list->data->coordinates == upTile)
		{
			app->render->DrawTexture(groundTex, position.x, position.y, &ground2);
			break;
		}
		else
		{
			app->render->DrawTexture(groundTex, position.x, position.y, &ground1);
		}
	}
}
