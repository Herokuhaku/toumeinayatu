#pragma once
#include "BaseScene.h"


class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	void Init(void)override;
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own) override;
	void Draw(void)override;
private:
	int img_;
	int frame_;
};