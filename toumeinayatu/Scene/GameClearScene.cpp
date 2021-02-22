#include <DxLib.h>
#include <string>
#include "GameClearScene.h"
#include "SceneMng.h"
#include "CrossOverScene.h"
#include "StageSelectScene.h"

GameClearScene::GameClearScene(int& makescreen)
{
	tmpscreen = makescreen;
	Init();
}

GameClearScene::~GameClearScene()
{
}

void GameClearScene::Init(void)
{
	screenID = MakeScreen(lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y,true);

	next_ = new NextButton(Vector2{1000,677}, Vector2{120,30});
}

std::unique_ptr<BaseScene> GameClearScene::Update(std::unique_ptr<BaseScene> own)
{
	Draw();
	if ((GetMouseInput() == MOUSE_INPUT_RIGHT) != 0)
	{
		return std::make_unique<CrossOverScene>(std::move(own),std::make_unique<StageSelectScene>());
	}
	if (!next_->Update())
	{
		return std::make_unique<CrossOverScene>(std::move(own),std::make_unique<StageSelectScene>());
	}
	return own;
}

void GameClearScene::Draw(void)
{
	SetDrawScreen(screenID);

	int size = GetFontSize();
	SetFontSize(48);
	std::string str = "GameClear";

	DrawString(lpSceneMng.GetScreenSize().x/2 - GetFontSize()/2 * (str.size()/2)+3,100+3,str.c_str(),0x0,true);
	DrawString(lpSceneMng.GetScreenSize().x / 2 - GetFontSize()/2 * (str.size() / 2),100, str.c_str(), 0xff0000, true);

	SetFontSize(size);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0,0,tmpscreen,true);
	DrawGraph(0, 0,screenID, true);
	next_->Draw();
}
