#pragma once
#include "common/Vector2.h"
class Stage
{
public:
	Stage(Vector2 pos,Vector2 size,int stageno);
	~Stage();
	bool Update(void);
	void Draw(void);
	int GetNo(void);
private:
	void Init();
	int screen_;
	Vector2 pos_;
	Vector2 windowSize_;
	int stageno_;
	bool selectflag_;
};

