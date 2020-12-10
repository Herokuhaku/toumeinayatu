#include <DxLib.h>
#include "Player.h"
#include "../Scene/GameScene.h"
#include "../AllControl/KeyBoardCtl.h"


Player::Player(Vector2 pos, Vector2 size,TmxData& map):map_(map)
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

		int frame = (static_cast<int>(pldir_)+4) + ((walk_++/15)%2)*4;
		DrawGraph(0,0,animation_[frame], true);

		SetDrawScreen(DX_SCREEN_BACK);
		DrawRotaGraph(pos_.x + num["tilewidth"]/2,pos_.y+size_.x/4,1.0f,0.0f, screen, true);
	}
}

void Player::Update(void)
{
	(*controller_)();
	checkpos_ = {pos_.x,pos_.y};
	for (auto& key : controller_->GetCntData())
	{
		keymove_[key.first](key);
	}
}

void Player::Init(void)
{
	objtype_ = ObjType::Player;
	screen = MakeScreen(size_.x, size_.y, true);
	animation_.resize(12);
	LoadDivGraph("Tiled/image/player.png",12, 4,3, size_.x, size_.y, animation_.data());

	controller_ = std::make_unique<KeyBoard>();
	if (controller_ != nullptr)
	{
		controller_->SetUp(0);
	}	
	KeyInit();

	for (auto& data : map_.num)
	{
		num[data.first] = std::atoi(data.second.c_str());
	}
	speed_ = 2;
}

void Player::KeyInit()
{
	keymove_.try_emplace(INPUT_ID::RIGHT, [&](std::pair<INPUT_ID, TrgBool> data) {
		if (data.second[static_cast<int>(Trg::Now)])
		{
			pldir_ = DIR::RIGHT;
			checkpos_.x += speed_ + num["tilewidth"];
			int check = (checkpos_.x / num["tilewidth"]) + ((checkpos_.y / num["tilewidth"]) * num["width"]);
			if (checkpos_.x < lpSceneMng.GetScreenSize().x && map_.MapData["Obj"][check] == 255)
			{
				pos_.x += speed_;
			}
		}
	});
	keymove_.try_emplace(INPUT_ID::LEFT, [&](std::pair<INPUT_ID, TrgBool> data) {
		if (data.second[static_cast<int>(Trg::Now)])
		{
			pldir_ = DIR::LEFT;
			checkpos_.x -= speed_;
			int check = (checkpos_.x / num["tilewidth"]) + ((checkpos_.y / num["tilewidth"]) * num["width"]);
			if (0 < checkpos_.x && map_.MapData["Obj"][check] == 255)
			{
				pos_.x-= speed_;
			}
		}
	});
	keymove_.try_emplace(INPUT_ID::UP, [&](std::pair<INPUT_ID, TrgBool> data) {
		if (data.second[static_cast<int>(Trg::Now)])
		{
			pldir_ = DIR::UP;
			checkpos_.y -= speed_;
			int check = (checkpos_.x / num["tilewidth"]) + ((checkpos_.y / num["tilewidth"]) * num["width"]);
			if (checkpos_.y > 0 &&map_.MapData["Obj"][check] == 255)
			{
				pos_.y -= speed_;
			}
		}
	});
	keymove_.try_emplace(INPUT_ID::DOWN, [&](std::pair<INPUT_ID, TrgBool> data) {
		if (data.second[static_cast<int>(Trg::Now)])
		{
			pldir_ = DIR::DOWN;
			checkpos_.y += speed_ + num["tilewidth"];
			int check = (checkpos_.x / num["tilewidth"]) + ((checkpos_.y / num["tilewidth"]) * num["width"]);
			if (checkpos_.y < lpSceneMng.GetScreenSize().y && map_.MapData["Obj"][check] == 255)
			{
				pos_.y += speed_;
			}
		}
	});
}
