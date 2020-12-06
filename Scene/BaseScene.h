#pragma once
#include <memory>

#define COUNT_LIMIT 15000
#define START_LIMIT 10000

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual void Init(void) = 0;
	virtual std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own) = 0;
	virtual void Draw(void);
	virtual void DrawOwnScreen(void);
	virtual void Draw(double ex, double rad);
protected:
	int screenID;
};

