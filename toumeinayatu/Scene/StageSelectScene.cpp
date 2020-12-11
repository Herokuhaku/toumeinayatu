#include <DxLib.h>
#include "StageSelectScene.h"
#include "SceneMng.h"
#include "GameScene.h"
#include "CrossOverScene.h"

StageSelectScene::StageSelectScene()
{
	Init();
}

StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::Init(void)
{
	nextStageNo_ = 0;
	Size_ = lpSceneMng.GetScreenSize();
	screenID = MakeScreen(Size_.x,Size_.y,true);
	stage_.emplace_back(Vector2(100,100),stage_.size());
}

std::unique_ptr<BaseScene> StageSelectScene::Update(std::unique_ptr<BaseScene> own)
{
	Draw();
	for (auto& stg : stage_)
	{
		if (!stg.Update())
		{
			return std::make_unique<CrossOverScene>(std::move(own),std::make_unique<GameScene>(stg.GetNo()));
		}
	}

	return own;
}

void StageSelectScene::Draw(void)
{
	SetDrawScreen(screenID);
	ClsDrawScreen();

	for (auto& stg : stage_)
	{
		stg.Draw();
	}

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0,0,screenID,true);
}
