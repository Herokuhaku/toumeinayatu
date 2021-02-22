#include <DxLib.h>
#include "GameOverScene.h"
#include "SceneMng.h"
#include "StageSelectScene.h"
#include "CrossOverScene.h"

GameOverScene::GameOverScene()
{
	Init();
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Init(void)
{
	screenID = MakeScreen(lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y);
	back = LoadGraph("Tiled/image/GameOver.png");
	title = LoadGraph("Tiled/image/ƒ^ƒCƒgƒ‹‚É–ß‚é.png");
}

std::unique_ptr<BaseScene> GameOverScene::Update(std::unique_ptr<BaseScene> own)
{
	Draw();
	if ((GetMouseInput() == MOUSE_INPUT_LEFT) != 0)
	{
		return std::make_unique<CrossOverScene>(std::move(own), std::make_unique<StageSelectScene>());
	}
	return own;
}

void GameOverScene::Draw(void)
{
	SetDrawScreen(screenID);
	ClsDrawScreen();
	DrawBox(0,0,lpSceneMng.GetScreenSize().x,lpSceneMng.GetScreenSize().y,0xffffff,true);
	DrawGraph(-200,0,back,true);

	DrawGraph(lpSceneMng.GetScreenSize().x/2-100, lpSceneMng.GetScreenSize().y / 2-300,title,true);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, screenID, true);
	frame++;
}
