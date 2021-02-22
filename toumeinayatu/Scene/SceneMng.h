#pragma once
#include <chrono>
#include <map>
#include "BaseScene.h"
#include "../common/Vector2.h"

#define lpSceneMng SceneMng::GetInstance()

enum class MOUSE__
{
	NON,
	LEFT,
	RIGHT,
	CENTER
};
class SceneMng
{
public:
	static SceneMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}
	static void Create(void)
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
	}
	static void Destroy(void)
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void Run(void);
	Vector2 GetScreenSize(void);
	std::chrono::system_clock::time_point GetNowTime() { return std::chrono::system_clock::now(); };
private:
	bool SysInit(void);
	const Vector2 _screenSize;
	std::unique_ptr<BaseScene> sceneNow_;

	SceneMng();
	~SceneMng();
	void Draw();
	int screenid_;
	std::map<MOUSE__, int> img_;
	static SceneMng* sInstance;
};