#pragma once
#include "BaseScene.h"
#include "../NextButton.h"

class GameClearScene :
	public BaseScene
{
public:
	GameClearScene(int& makescreen);
	~GameClearScene();
	void Init(void)override;
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own)override;
	void Draw(void)override;
private:
	int tmpscreen;
	NextButton* next_;
};

