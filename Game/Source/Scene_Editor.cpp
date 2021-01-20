#include "App.h"
#include "Scene_Editor.h"
#include "Render.h"
#include "Window.h"

#define WIN_HEIGHT 574
#define WIN_WIDTH 1024
#define H_MARGIN (720 - WIN_HEIGHT) / 2
#define W_MARGIN (1280 - WIN_WIDTH) / 2

SceneEditor::SceneEditor()
{

}

SceneEditor::~SceneEditor()
{
}

void SceneEditor::DrawGrid()
{
	DebugMargin(debugMargin);

	for (int i = 1; i < 25; i++)
	{
		app->render->DrawLine(W_MARGIN + (41 * i), H_MARGIN, W_MARGIN + (41 * i), WIN_HEIGHT + H_MARGIN, { 255, 255, 255, 255 });
	}

	for (int i = 1; i < 14; i++)
	{
		app->render->DrawLine(W_MARGIN, H_MARGIN + (41 * i), WIN_WIDTH + W_MARGIN, H_MARGIN + (41 * i), { 255, 255, 255, 255 });
	}
}

void SceneEditor::DebugMargin(bool debug)
{
	if (debug)
	{
		app->render->DrawLine(W_MARGIN, H_MARGIN, WIN_WIDTH + W_MARGIN, H_MARGIN, { 255, 255, 255, 100 });
		app->render->DrawLine(W_MARGIN, H_MARGIN, W_MARGIN, WIN_HEIGHT + H_MARGIN, { 255, 255, 255, 100 });
		app->render->DrawLine(W_MARGIN, WIN_HEIGHT + H_MARGIN, WIN_WIDTH + W_MARGIN, WIN_HEIGHT + H_MARGIN, { 255, 255, 255, 80 });
		app->render->DrawLine(WIN_WIDTH + W_MARGIN, H_MARGIN, WIN_WIDTH + W_MARGIN, WIN_HEIGHT + H_MARGIN, { 255, 255, 255, 80 });
	}
}