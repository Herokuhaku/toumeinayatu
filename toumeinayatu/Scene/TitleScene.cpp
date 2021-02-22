#include <DxLib.h>
#include "TitleScene.h"
#include "SceneMng.h"
#include "CrossOverScene.h"
#include "StageSelectScene.h"

TitleScene::TitleScene()
{
	Init();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init(void)
{
	screenID = MakeScreen(lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y);
	img_ = LoadGraph("Tiled/image/TitleScenehaikei.png");
}

std::unique_ptr<BaseScene> TitleScene::Update(std::unique_ptr<BaseScene> own)
{
	Draw();
	if ((GetMouseInput() == MOUSE_INPUT_LEFT) != 0)
	{
		return std::make_unique<CrossOverScene>(std::move(own), std::make_unique<StageSelectScene>());
	}
	if (frame_++ >= 30000)
	{
		return std::make_unique<CrossOverScene>(std::move(own), std::make_unique<StageSelectScene>());
	}
	return own;
}

void TitleScene::Draw(void)
{
	SetDrawScreen(screenID);
	ClsDrawScreen();

	//DrawBox(0, 0, lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y, 0xCCCCCC, true);
	DrawGraph(0,0,img_,true);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, screenID, true);
}