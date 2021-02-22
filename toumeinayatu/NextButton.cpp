#include <DxLib.h>
#include <string>
#include "NextButton.h"

NextButton::NextButton(Vector2 pos, Vector2 size):size_(size)
{
	pos_ = pos;
	Init();
}

NextButton::~NextButton()
{
}

bool NextButton::Update(void)
{
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		pos_.x += 1;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		pos_.x -= 1;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		pos_.y -= 1;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		pos_.y += 1;
	}

	Vector2 mouse;
	GetMousePoint(&mouse.x, &mouse.y);
	if (pos_.x < mouse.x && mouse.x < size_.x + pos_.x &&
		pos_.y < mouse.y && mouse.y < size_.y + pos_.y)
	{
		flag_ = true;
		if ((GetMouseInput() == MOUSE_INPUT_LEFT) != 0)
		{
			return false;
		}
	}
	else { flag_ = false; }
	return true;
}

void NextButton::Draw(void)
{
	SetDrawScreen(screen_);
	DrawBox(0,0,size_.x,size_.y,0x0,true);
	if (flag_) {
		for (int i = 0;i < 3;i++)
		{
			DrawBox(0 + i, 0 + i, size_.x - i, size_.y - i, 0xff0000, false);
		}
	}
	std::string str = "ステージ選択へ戻る";
	DrawFormatString(0, 5, 0xff00ff, str.c_str());

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(pos_.x, pos_.y, screen_, true);
}

void NextButton::Init(void)
{
	screen_ = MakeScreen(size_.x,size_.y, true);
}
