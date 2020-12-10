#pragma once
#include <vector>
#include "BaseScene.h"
#include "../Stage.h"

class StageSelectScene :
	public BaseScene
{
public:
	StageSelectScene();
	~StageSelectScene();
	void Init(void);
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own);
private:
	void Draw(void)override;
	int nextStageNo_;


	std::vector<Stage> stage_;
	Vector2 Size_;
};

