#include <DxLib.h>
#include "SoundMng.h"

SoundMng* SoundMng::sInstance = nullptr;

void SoundMng::PushLoop(int music)
{
	loop_ = music;
	ChangeVolumeSoundMem(255,music);
}

void SoundMng::DeleteLoop()
{
	StopSoundMem(loop_);
	loop_ = -1;
}

void SoundMng::PlayLoop(void)
{
	StopSoundMem(loop_);
	PlaySoundMem(loop_, DX_PLAYTYPE_LOOP);
}

void SoundMng::LoadLoop(const char* filename)
{
	loop_ = LoadSoundMem(filename);
}

SoundMng::SoundMng()
{
}

SoundMng::~SoundMng()
{
}
