#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
	Init();
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Init(void)
{
}

std::unique_ptr<BaseScene> GameOverScene::Update(std::unique_ptr<BaseScene> own)
{
	return own;
}

void GameOverScene::Draw(void)
{
}
