#include "XboxController.h"

int XboxController::count_ = 0;

ControlType XboxController::GetType(void)
{
	return ControlType::XBOX_CONTROLLER;
}

bool XboxController::SetUp(int no)
{
	_keyList.try_emplace(INPUT_ID::UP, XINPUT_BUTTON_DPAD_UP);
	_keyList.try_emplace(INPUT_ID::DOWN, XINPUT_BUTTON_DPAD_DOWN);
	_keyList.try_emplace(INPUT_ID::LEFT, XINPUT_BUTTON_DPAD_LEFT);
	_keyList.try_emplace(INPUT_ID::RIGHT, XINPUT_BUTTON_DPAD_RIGHT);

	id_ = count_++;
	return true;
}

void XboxController::Update(void)
{
	GetJoypadXInputState(id_+1, &input);
	// �X�V
	for (auto id : INPUT_ID())
	{
		_data[id][static_cast<int>(Trg::Old)] = _data[id][static_cast<int>(Trg::Now)];
		_data[id][static_cast<int>(Trg::Now)] = input.Buttons[_keyList[id]];
	}
	StickUp();
}

void XboxController::StickUp(void)
{
	// ���X�e�B�b�N��X��
	if (input.ThumbLX > 30000)
	{
		_data[INPUT_ID::RIGHT][static_cast<int>(Trg::Now)] = 1;
	}
	else if (input.ThumbLX < -30000)
	{
		_data[INPUT_ID::LEFT][static_cast<int>(Trg::Now)] = 1;
	}
	else
	{
		_data[INPUT_ID::LEFT][static_cast<int>(Trg::Now)] = 0;
		_data[INPUT_ID::RIGHT][static_cast<int>(Trg::Now)] = 0;
	}
	// ���X�e�B�b�N��Y��
	if (input.ThumbLY > 30000)
	{
		_data[INPUT_ID::UP][static_cast<int>(Trg::Now)] = 1;
	}
	else if (input.ThumbLY < -30000)
	{
		_data[INPUT_ID::DOWN][static_cast<int>(Trg::Now)] = 1;
	}
	else
	{
		_data[INPUT_ID::DOWN][static_cast<int>(Trg::Now)] = 0;
		_data[INPUT_ID::UP][static_cast<int>(Trg::Now)] = 0;
	}
}
