#pragma once
#include <map>
#include <memory>
#include <functional>
#include "Obj.h"
#include "../AllControl/Control.h"
#include "../AllControl/INPUT_ID.h"
#include "../Tiled/TiledLoader.h"

enum class DIR
{
	DOWN,
	LEFT,
	RIGHT,
	UP,
};

class Player :
	public Obj
{
public:
	Player(Vector2 pos,Vector2 size,TmxData& map);
	~Player();
	void Draw(void)override;
	void Update(void)override;
	void Init(void)override;
private:
	// ëÄçÏ
	void KeyInit();
	TmxData& map_;
	std::unique_ptr<Control> controller_;
	std::map < INPUT_ID, std::function<void(std::pair<INPUT_ID, TrgBool>)>> keymove_;
	DIR pldir_;
	int walk_;
	int speed_;
	std::map<std::string, int> num;
	Vector2 checkpos_;
};

