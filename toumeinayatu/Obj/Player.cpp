#include <DxLib.h>
#include "Player.h"
#include "../Scene/GameScene.h"
#include "../AllControl/KeyBoardCtl.h"


Player::Player(Vector2 pos, Vector2 size)
{
	pos_ = pos;
	size_ = size;
	Init();
}

Player::~Player()
{
}

void Player::Draw(void)
{
	if (alive_)
	{
		SetDrawScreen(screen);
		ClsDrawScreen();

		SetDrawScreen(DX_SCREEN_BACK);
	}
}

void Player::Update(void)
{

}

void Player::Init(void)
{
	objtype_ = ObjType::Player;

	//animation_.resize(20);
	//LoadDivGraph("Tiled/image/bomberman.png", 20, 5, 4, size_.x, size_.y, animation_.data());

	screen = MakeScreen(size_.x,size_.y,true);
	controller_ = std::make_unique<KeyBoard>();
	if (controller_ != nullptr)
	{
		controller_->SetUp(0);
	}	
	KeyInit();
}

void Player::KeyInit()
{
	keymove_.try_emplace(INPUT_ID::RIGHT, [&](std::pair<INPUT_ID, TrgBool> data) {
		if (data.second[static_cast<int>(Trg::Now)])
		{
			pos_.x++;
		}
	});
	keymove_.try_emplace(INPUT_ID::LEFT, [&](std::pair<INPUT_ID, TrgBool> data) {
		if (data.second[static_cast<int>(Trg::Now)])
		{
			pos_.x--;
		}
	});
	keymove_.try_emplace(INPUT_ID::UP, [&](std::pair<INPUT_ID, TrgBool> data) {
		if (data.second[static_cast<int>(Trg::Now)])
		{
			pos_.y--;
		}
	});
	keymove_.try_emplace(INPUT_ID::DOWN, [&](std::pair<INPUT_ID, TrgBool> data) {
		if (data.second[static_cast<int>(Trg::Now)])
		{
			pos_.y++;
		}
	});
}
