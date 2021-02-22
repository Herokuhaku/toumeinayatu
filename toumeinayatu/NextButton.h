#pragma once
#include "common/Vector2.h"
#include "Scene/BaseScene.h"
class NextButton
{
public:
	NextButton(Vector2 pos, Vector2 size);
	~NextButton();
	bool Update(void);
	void Draw(void);
	void Init(void);
private:
	Vector2 pos_;
	const Vector2 size_;
	int screen_;
	bool flag_;
};

