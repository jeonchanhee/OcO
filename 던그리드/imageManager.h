#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*>				mapImageList;
	typedef map<string, image*>::iterator	mapImageIter;

private:
	mapImageList _mImageList;

public:
	imageManager();
	~imageManager();

	HRESULT init(void);
	void release(void);

	image* addImage(string strKey, int width, int height, BOOL blend = FALSE);
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor, BOOL blend = FALSE);
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor, BOOL blend = FALSE);

	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, BOOL blend = FALSE);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, BOOL blend = FALSE);

	image * addRotateImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor, BOOL blend = FALSE);

	image * addRotateFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, BOOL blend = FALSE);


	//rotate
	image* addRotateImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	image* addRotateFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	//rotate
	void rotateRender(string strKey, HDC hdc, float x, float y, float angle);
	void rotateFrameRender(string strKey, HDC hdc, float x, float y, float angle);
	//키 값 찾는 함수
	image* findImage(string strKey);

	//싱글톤화 되어있는 이미지 지워주는 함수
	BOOL deleteImage(string strKey);

	//모든 이미지 제거 함수
	BOOL deleteAll(void);

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//프레임렌더 + 루프렌더는 여러분이 추가해보세영~
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void rotateRender(string strKey, HDC hdc, float x, float y, float angle);

	void rotateFrameRender(string strKey, HDC hdc, float x, float y, float angle);
	
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void alphaLoopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);

};

