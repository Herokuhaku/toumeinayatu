#pragma once
#include <vector>
#include <memory>
#include "../common/Vector2.h"

enum class ObjType
{
	Obj,
	Player,
	Bomb,
	Fire
};

class Obj
{
public:
	Obj();
	Obj(Vector2 pos,Vector2 size);
	~Obj();
	virtual void Draw(void) = 0;
	virtual void Update(void) = 0;
	virtual void Init(void) = 0;
protected:
	Vector2 pos_;
	Vector2 size_;
	int id_;
	int screen;
	bool alive_;
	std::vector<int> animation_;
	bool deleteflag_;
	ObjType objtype_;
private:
};

