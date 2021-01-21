#include "App.h"
#include "Render.h"
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
	app->render->DrawTexture(groundTex, position.x, position.y, &typeRect);
	app->render->DrawRectangle(groundRect, {30, 30, 200, 100});
}
