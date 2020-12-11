#pragma once
#include "BaseScene.h"

class GameOverScene :
	public BaseScene
{
public:
	GameOverScene();
	~GameOverScene();
	void Init(void)override;
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own)override;
	void Draw(void)override;
};

