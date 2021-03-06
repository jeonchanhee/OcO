#pragma once
#include "singletonBase.h"
#include <map>

#include "inc/fmod.hpp"

#pragma comment(lib, "lib/fmodex64_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 30
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

enum SOUNDTYPE {BGM, SFX};

class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;
	typedef map<string, SOUNDTYPE>  arrSoundsType;
	typedef map<string, SOUNDTYPE>::iterator arrSoundsTypeIter;

private:
	System * _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;
	arrSoundsType _mSoundsType;

	float _bgmVol, _sfxVol;

public:
	HRESULT init();
	void release();
	void update();

	void addSound(string keyName, string soundName, bool bgm, bool loop);
	void play(string keyName, float volume = 1.0f); // 0.0 ~ 1.0f -> 0 ~ 255
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

	int getLength(string keyName);

	int getPlayTime(string keyName);

	void setPlayTime(string keyName, unsigned int time);

	void setVolume(string keyName, float volume);

	void setBGMVolume(float volume);

	void setSFXVolume(float volume);

	//float getVolume(string keyName);


	soundManager();
	~soundManager();
};

