#pragma once
#include <map>
#include <memory>
#include <functional>
#include "Obj.h"
#include "../AllControl/Control.h"
#include "../AllControl/INPUT_ID.h"

class Player :
	public Obj
{
public:
	Player(Vector2 pos,Vector2 size);
	~Player();
	void Draw(void)override;
	void Update(void)override;
	void Init(void)override;
private:
	// ëÄçÏ
	void KeyInit();
	std::unique_ptr<Control> controller_;
	std::map < INPUT_ID, std::function<void(std::pair<INPUT_ID, TrgBool>)>> keymove_;

};

