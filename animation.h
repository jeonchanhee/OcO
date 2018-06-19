#pragma once
#include <vector>

class animation
{
public:
	typedef vector<POINT>	vFrameList;
	typedef vector<int>		vPlayList;

private:
	
	int				_frameNum;		//애니메이션 프레임 갯수
	vFrameList		_frameList;		//프레임 리스트
	vPlayList		_playList;		//플레이 리스트

	int				_frameWidth;	//프레임 가로크기
	int				_frameHeight;	//프레임 세로크기

	BOOL			_loop;			//애니메이션 루프여부

	float			_frameUpdateSec;//한 프레임 
	float			_elapsedSec;	//경과시간

	DWORD			_nowPlayIndex;	//현재 플레이 인덱스
	BOOL			_play;			//플레이 여부
public:
	animation();
	~animation();

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);

	//디폴트 애니메이션 재생
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	//배열 애니메이션 재생
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	//구간 애니메이션 재생
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);

	//애니메이션 프레임 재생속도 셋팅
	void setFPS(int framePerSec);

	//렌더링
	void frameUpdate(float elapsedTime);

	void start();
	void stop();
	void pause();
	void resume();

	inline BOOL isPlay() { return _play; }
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }

};

