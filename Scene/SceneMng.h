#pragma once
#include "BaseScene.h"
#include "../common/Vector2.h"

#define lpSceneMng SceneMng::GetInstance()

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
private:
	bool SysInit(void);
	const Vector2 _screenSize;
	std::unique_ptr<BaseScene> sceneNow_;

	SceneMng();
	~SceneMng();
	
	static SceneMng* sInstance;
};