#include <DxLib.h>
#include <time.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "CrossOverScene.h"

 SceneMng* SceneMng::sInstance = nullptr;

 void SceneMng::Run(void)
 {
	 sceneNow_ = std::make_unique<GameScene>();
	 while (!ProcessMessage())
	 {
		 SetDrawScreen(DX_SCREEN_BACK);
		 ClsDrawScreen();

		 sceneNow_ = sceneNow_->Update(std::move(sceneNow_));

		 ScreenFlip();
	 }
 }

Vector2 SceneMng::GetScreenSize(void)
{
	return _screenSize;
}

bool SceneMng::SysInit(void)
{
	SetWindowText("“§–¾‚È‚â‚Â");
	SetGraphMode(_screenSize.x, _screenSize.y, 16);
	ChangeWindowMode(true);
	if (DxLib::DxLib_Init() == -1)
	{
		return false;
	}
	srand(static_cast<unsigned int>(time(NULL)));
	SetDoubleStartValidFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);
	return true;
}

SceneMng::SceneMng() :_screenSize(1280,720)
{
	SysInit();
}

SceneMng::~SceneMng()
{
}
