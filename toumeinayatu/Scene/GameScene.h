#pragma once
#include "BaseScene.h"
#include "SceneMng.h"
#include "../Tiled/TiledLoader.h"
#include "../Obj/Obj.h"


class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	void Init(void)override;
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own) override;
	void Draw(void)override;
	void Draw(double ex, double rad)override;
private:
	std::vector<TmxData> stagedata_;
	TsxData stagetsx_;
	std::map<std::string,int> num;
	std::vector<int> Image;
	Vector2 offset_;
	int stageNo_;
	std::vector<std::unique_ptr<Obj>> objlist_;
};