#pragma once
#include <vector>

#define lpSoundMng SoundMng::GetInstance()

class SoundMng
{
public:
	static SoundMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}
	static void Create(void)
	{
		if (sInstance == nullptr)
		{
			sInstance = new SoundMng();
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
	void PushLoop(int);
	void DeleteLoop();
	void PlayLoop(void);
	void LoadLoop(const char* filename);
private:
	SoundMng();
	~SoundMng();
	static SoundMng* sInstance;

	int loop_;
	std::vector<int> soundeffect_;
};

