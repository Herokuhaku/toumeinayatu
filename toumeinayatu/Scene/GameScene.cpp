#include <DxLib.h>
#include "GameScene.h"
#include "CrossOverScene.h"
#include "StageSelectScene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "../Obj/Player.h"
#include "../Manage/SoundMng.h"

GameScene::GameScene(int stageno)
{
	stageNo_ = stageno;
	Init();
}

GameScene::~GameScene()
{
	lpSoundMng.DeleteLoop();
}

void GameScene::Init(void)
{
	screenID = MakeScreen(lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y);
	std::string stage = "Tiled/mapdata/stage";
	stage += std::to_string(stageNo_);
	stagedata_ = lpTiledLoader.ReadTmx(stage);
	stagetsx_ = lpTiledLoader.ReadTsx("Tiled/mapdata/Tile");

	for (auto& data : stagedata_.num)
	{
		num[data.first] = std::atoi(data.second.c_str());
	}

	Image.resize(16);
	LoadDivGraph(stagetsx_.pass.c_str(), 16,
		4, 4, num["tilewidth"], num["tileheight"], &Image[0]);

	int pos = 0;
	for (auto& pl : stagedata_.MapData["Char"])
	{
		if (pl != 255)
		{
			objlist_.emplace_back(new Player(Vector2(pos % num["width"] * num["tilewidth"], pos / num["tileheight"] * num["tileheight"]), Vector2{ 32,48 },
				stagedata_));
			break;
		}
		pos++;
	}

	ready_ = false;
	readycount_ = false;
	viewtime_ = 50;

	lpSoundMng.PushLoop(LoadSoundMem("musicdata/fantasy08.mp3"));
	lpSoundMng.PlayLoop();
}

std::unique_ptr<BaseScene> GameScene::Update(std::unique_ptr<BaseScene> own)
{

	Draw();
	for (auto& obj : objlist_)
	{
		if (ready_)
		{
			if (obj->Update() == Game::CLEAR)
			{
				ready_ = false;
				Draw();
				obj->Draw();
				return std::make_unique<GameClearScene>(screenID);
			}
			else if (obj->Update() == Game::OVER)
			{
				return std::make_unique<CrossOverScene>(std::move(own), std::make_unique<GameOverScene>());
			}
		}
		obj->Draw();
	}
	Ready();
	//sound++;
	return own;
}

void GameScene::Draw(void)
{
	SetDrawScreen(screenID);
	ClsDrawScreen();

	DrawBox(0, 0, lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y, 0xCCCCCC, true);
	int w = num["width"];
	int tw = num["tilewidth"];
	int th = num["tileheight"];
	for (auto& data : stagedata_.MapData)
	{
		if ((data.first == "Obj") && (ready_ && view_)) {
			continue;
		}
		int x = 0, y = 0;
		for (auto& no : data.second)
		{
			if (0 <= no && 16 > no) {
				DrawRotaGraph(x * tw + tw / 2, y *  th+ th / 2, 1.0f, 0.0f, Image[no], true);
			}
			x++;
			if (x >= w) { y++; x = 0; }
		}
	}
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, screenID, true);
}

void GameScene::Draw(double ex, double rad)
{
	SetDrawScreen(screenID);
	ClsDrawScreen();

	SetDrawScreen(DX_SCREEN_BACK);
	DrawRotaGraph(lpSceneMng.GetScreenSize().x/2, lpSceneMng.GetScreenSize().y / 2,ex,rad, screenID, true);
}

void GameScene::Ready(void)
{
	int size = GetFontSize();
	SetFontSize(48);
	if (!ready_)
	{
		if (readycount_ > 300)
		{
			ready_ = true;
		}
		DrawFormatString(20, 32 * 20 + 25, 0x0, "%d", 300 / 60 - readycount_++ / 60);
		DrawFormatString(22, 32 * 20 + 27,0xff0000,"%d",300/60 - readycount_++/60);
	}
	else
	{
		DrawFormatString(20, 32 * 20 + 25, 0x0, "Žc‚è %d  frame", viewtime_ - viewcount_);
		DrawFormatString(22, 32 * 20 + 27, 0xff0000, "Žc‚è %d  frame", viewtime_  - viewcount_);
		if ((GetMouseInput() == MOUSE_INPUT_RIGHT) && (viewtime_  - viewcount_ ) > 0)
		{
			viewcount_++;
			view_ = false;
		}
		else
		{
			view_ = true;
		}
	}
	SetFontSize(size);
}
