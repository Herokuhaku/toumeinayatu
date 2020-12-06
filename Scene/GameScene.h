#pragma once
#include "BaseScene.h"
#include "SceneMng.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	void Init(void)override;
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own) override;
	void Draw(void)override;
	void Draw(double ex, double rad)override;
private:
};