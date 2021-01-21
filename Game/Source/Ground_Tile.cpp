#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Ground_Tile.h"

GroundTile::GroundTile()
{

}

GroundTile::GroundTile(int x, int y)
{
	groundTex = app->tex->Load("Assets/Tilesets/ground_tileset.png");
	position.x = x;
	position.y = y;
	groundRect = {x, y, 41, 41};
}

GroundTile::~GroundTile()
{
}

void GroundTile::Draw()
{
	app->render->DrawTexture(groundTex, position.x, position.y, &typeRect);
	app->render->DrawRectangle(groundRect, {30, 30, 200, 100});
}
