#include <DxLib.h>
#include "GameScene.h"
#include "../Obj/Player.h"

GameScene::GameScene(int stageno)
{
	stageNo_ = stageno;
	Init();
}

GameScene::~GameScene()
{
}

void GameScene::Init(void)
{
	screenID = MakeScreen(lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y);
	std::string stage = "Tiled/mapdata/stage";
	stage += std::to_string(stageNo_);
	stagedata_.emplace_back(lpTiledLoader.ReadTmx(stage));
	stagetsx_ = lpTiledLoader.ReadTsx("Tiled/mapdata/Tile");

	for (auto& data : stagedata_[stageNo_].num)
	{
		num[data.first] = std::atoi(data.second.c_str());
	}
	Image.resize(16);
	LoadDivGraph(stagetsx_.pass.c_str(), 16,
		4, 4, num["tilewidth"], num["tileheight"], &Image[0]);
	
	int pos = 0;
	for (auto& pl : stagedata_[stageNo_].MapData["Char"])
	{
		if (pl != 255)
		{
			objlist_.emplace_back(new Player(Vector2(pos % num["width"] * num["tilewidth"], pos / num["tileheight"] * num["tileheight"]), Vector2{ 32,48 },
				stagedata_[stageNo_]));
			break;
		}
		pos++;
	}
}

std::unique_ptr<BaseScene> GameScene::Update(std::unique_ptr<BaseScene> own)
{
	Draw();
	for (auto& obj : objlist_)
	{
		obj->Update();
		obj->Draw();
	}
	return own;
}

void GameScene::Draw(void)
{
	SetDrawScreen(screenID);
	ClsDrawScreen();

	DrawBox(0, 0, lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y, 0xCCCCCC, true);

	for (auto& data : stagedata_[stageNo_].MapData)
	{
		int x = 0, y = 0;
		for (auto& no : data.second)
		{
			if (0 <= no && 16 > no) {
				DrawRotaGraph(x * num["tilewidth"] + num["tilewidth"]/2,y * num["tileheight"] + num["tileheight"]/2, 1.0f, 0.0f, Image[no], true);
			}
			x++;
			if (x >= num["width"]) { y++; x = 0; }
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
