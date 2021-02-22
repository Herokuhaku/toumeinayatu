#include <DxLib.h>
#include <string>
#include "Stage.h"

Stage::Stage(Vector2 pos,Vector2 size,int stageno)
{
	pos_ = pos;
	stageno_ = stageno;
	windowSize_ = size;
	Init();
}

Stage::~Stage()
{
}

bool Stage::Update(void)
{
	Vector2 mouse;
	GetMousePoint(&mouse.x, &mouse.y);
	if (pos_.x < mouse.x && mouse.x < windowSize_.x + pos_.x &&
		pos_.y < mouse.y && mouse.y < windowSize_.y + pos_.y)
	{
		selectflag_ = true;
		if ((GetMouseInput() == MOUSE_INPUT_LEFT) != 0)
		{
			return false;
		}
	}
	else { selectflag_ = false; }
	return true;
}

void Stage::Draw(void)
{
	SetDrawScreen(screen_);
	ClsDrawScreen();
	int before = GetFontSize();
	SetFontSize(24);
	int font_ = 24;
	DrawBox(0,0,windowSize_.x,windowSize_.y,0x99ff99,true);
	std::string str = "StageNo : %d";
	//std::string str = "%d";
	DrawFormatString(windowSize_.x/2 - ((str.size()*(font_/2)) /2),windowSize_.y/2-(font_),0x0,str.c_str(),stageno_+1);
	if (selectflag_)
	{
		for (int i = 0;i < 5;i++)
		{
			DrawBox(0+i, 0+i, windowSize_.x-i, windowSize_.y-i, 0xff0000, false);
		}
	}
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(pos_.x,pos_.y,screen_,true);

	SetFontSize(before);
}

int Stage::GetNo(void)
{
	return stageno_;
}

void Stage::Init()
{
	//windowSize_ = {300,200};
	screen_ = MakeScreen(windowSize_.x,windowSize_.y);
	selectflag_ = false;
}
