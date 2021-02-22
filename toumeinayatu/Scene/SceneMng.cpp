#include <DxLib.h>
#include <time.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "CrossOverScene.h"
#include "StageSelectScene.h"
#include "TitleScene.h"
#include "../_debug/_DebugDispOut.h"
#include "../Manage/SoundMng.h"

 SceneMng* SceneMng::sInstance = nullptr;

 void SceneMng::Run(void)
 {
	 sceneNow_ = std::make_unique<TitleScene>();
	 _dbgSetDrawPosFps(FPS_SIDE::LEFT, FPS_VER::TOP);
	 //sceneNow_ = std::make_unique<GameScene>(0);
	 while (!ProcessMessage())
	 {
		 _dbgStartDraw();
		 SetDrawScreen(DX_SCREEN_BACK);
		 ClsDrawScreen();

		 sceneNow_ = sceneNow_->Update(std::move(sceneNow_));
		 //_dbgDrawFPS();
		 Draw();
		 _dbgAddDraw();
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
	
	screenid_ = MakeScreen(_screenSize.x, _screenSize.y);
	lpSoundMng.LoadLoop("musicdata/fantasy08.mp3");
	img_.try_emplace(MOUSE__::NON, LoadGraph("Tiled/image/mouse.png"));
	img_.try_emplace(MOUSE__::LEFT,LoadGraph("Tiled/image/mouse_left.png"));
	img_.try_emplace(MOUSE__::RIGHT, LoadGraph("Tiled/image/mouse_right.png"));
	img_.try_emplace(MOUSE__::CENTER, LoadGraph("Tiled/image/mouse_center.png"));
	return true;
}

SceneMng::SceneMng() :_screenSize(32*35,32*20+100)
{
	SysInit();
}

SceneMng::~SceneMng()
{
}

void SceneMng::Draw()
{
	DrawGraph(_screenSize.x/2,680,img_[MOUSE__::NON],true);
	auto inp = GetMouseInput();
	if ((inp == MOUSE_INPUT_LEFT))
	{
		DrawGraph(_screenSize.x / 2, 680, img_[MOUSE__::LEFT], true);
	}
	if ((inp == MOUSE_INPUT_RIGHT))
	{
		DrawGraph(_screenSize.x / 2, 680, img_[MOUSE__::RIGHT], true);
	}
	if ((inp == MOUSE_INPUT_MIDDLE))
	{
		DrawGraph(_screenSize.x / 2, 680, img_[MOUSE__::CENTER], true);
	}
}
