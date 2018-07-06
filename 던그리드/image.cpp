#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")


image::image()
	: _imageInfo(NULL), 
	_fileName(NULL),
	_trans(FALSE),
	_transColor(RGB(0, 0, 0))
{
}


image::~image()
{
}

HRESULT image::init(int width, int height, BOOL blend)
{
	//����۰� ���� �ƴϸ� == ���� �����Ͱ� ������ == �ʱ�ȭ�� �߾ȵǾ�������
	//�����ض�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //���ο� �� DC������ �����
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);	//�� ��Ʈ���� �ϳ� �����
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;


	if (blend)
	{
		//���ĺ��� ����
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
	}

	_blend = blend;
	//����ó�� �ϳ� ��
	//��Ʈ���� �����ȵǾ��ٸ�
	if (_imageInfo->hBit == NULL)
	{
		//�������ְ�
		release();

		//�����ߴٰ� ȣ��â�� �����
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(int width, int height, BOOL trans, COLORREF transColor, BOOL blend)
{
	//����۰� ���� �ƴϸ� == ���� �����Ͱ� ������ == �ʱ�ȭ�� �߾ȵǾ�������
	//�����ض�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //���ο� �� DC������ �����
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);	//�� ��Ʈ���� �ϳ� �����
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;


	if (blend)
	{
		//���ĺ��� ����
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
	}

	_trans = trans;
	_transColor = transColor;

	_blend = blend;
	//����ó�� �ϳ� ��
	//��Ʈ���� �����ȵǾ��ٸ�
	if (_imageInfo->hBit == NULL)
	{
		//�������ְ�
		release();

		//�����ߴٰ� ȣ��â�� �����
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor, BOOL blend)
{
	//�����̸��� ������ ������ ������
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �����̶� ���������� ������
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	if (blend)
	{
		//���ĺ��� ����
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
	}

	int len = strlen(fileName);

	//���ϰ�� �� �̸� �޾ƿ´�
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//Ư���÷� �������� ���� �� �÷� ��
	_trans = trans;
	_transColor = transColor;

	_blend = blend;

	//�̹����� ����� �ҷ������� �ʾҴٸ�
	if (_imageInfo->hBit == NULL)
	{
		//�����ϰ� ������ �������
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	
	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor, BOOL blend)
{
	//�����̸��� ������ ������ ������
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �����̶� ���������� ������
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;


	if (blend)
	{
		//���ĺ��� ����
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
	}

	int len = strlen(fileName);

	//���ϰ�� �� �̸� �޾ƿ´�
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//Ư���÷� �������� ���� �� �÷� ��
	_trans = trans;
	_transColor = transColor;

	_blend = blend;

	//�̹����� ����� �ҷ������� �ʾҴٸ�
	if (_imageInfo->hBit == NULL)
	{
		//�����ϰ� ������ �������
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::rotateInit(const char * fileName, int width, int height, BOOL trans, COLORREF transColor, BOOL blend)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;



	//rotate

	int size;
	(width > height ? size = width : size = height);
	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_EMPTY;
	_rotateImage->resID = 0;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = size;
	_rotateImage->height = size;

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::rotateInit(int width, int height, BOOL trans, COLORREF transColor, BOOL blend)
{


	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //���ο� �� DC������ �����
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);	//�� ��Ʈ���� �ϳ� �����
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;




	//rotate

	int size;
	(width > height ? size = width : size = height);
	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_EMPTY;
	_rotateImage->resID = 0;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = size;
	_rotateImage->height = size;

	_trans = trans;
	_transColor = transColor;

	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::rotateInit(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL blend)
{
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �����̶� ���������� ������
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int size;
	(width > height ? size = width : size = height);
	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_EMPTY;
	_rotateImage->resID = 0;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = size;
	_rotateImage->height = size;



	int len = strlen(fileName);

	//���ϰ�� �� �̸� �޾ƿ´�
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//Ư���÷� �������� ���� �� �÷� ��
	_trans = trans;
	_transColor = transColor;

	//�̹����� ����� �ҷ������� �ʾҴٸ�
	if (_imageInfo->hBit == NULL)
	{
		//�����ϰ� ������ �������
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL blend)
{
	//�����̸��� ������ ������ ������
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �����̶� ���������� ������
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;


	if (blend)
	{
		//���ĺ��� ����
		_blendFunc.BlendFlags = 0;			//���ĺ��带 ����ϰڴٰ� �ʱ�ȭ
		_blendFunc.AlphaFormat = 0;			//���ĺ��忡 �ʿ��� �������� �ʱ�ȭ
		_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰Ÿ��� ������� �����غ���

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
	}

	int len = strlen(fileName);

	//���ϰ�� �� �̸� �޾ƿ´�
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//Ư���÷� �������� ���� �� �÷� ��
	_trans = trans;
	_transColor = transColor;


	_blend = blend;

	//�̹����� ����� �ҷ������� �ʾҴٸ�
	if (_imageInfo->hBit == NULL)
	{
		//�����ϰ� ������ �������
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL blend)
{
	//�����̸��� ������ ������ ������
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �����̶� ���������� ������
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	if (blend)
	{
		//���ĺ��� ����
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
	}

	int len = strlen(fileName);

	//���ϰ�� �� �̸� �޾ƿ´�
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//Ư���÷� �������� ���� �� �÷� ��
	_trans = trans;
	_transColor = transColor;

	_blend = blend;

	//�̹����� ����� �ҷ������� �ʾҴٸ�
	if (_imageInfo->hBit == NULL)
	{
		//�����ϰ� ������ �������
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release(void)
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = FALSE;
	}
}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� DC
			_imageInfo->x,			//����� ��ǥ X(left)
			_imageInfo->y,			//����� ��ǥ Y(top)
			_imageInfo->width,		//����� ����ũ��
			_imageInfo->height,		//����� ����ũ��
			_imageInfo->hMemDC,		//������ DC
			0, 0,					//������ x,y
			_imageInfo->width,		//������ ����, ����ũ��
			_imageInfo->height,
			_transColor);			//�����Ҷ� ������ Į��
	}
	else
	{
		BitBlt(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� DC
			destX,					//����� ��ǥ X(left)
			destY,					//����� ��ǥ Y(top)
			_imageInfo->width,		//����� ����ũ��
			_imageInfo->height,		//����� ����ũ��
			_imageInfo->hMemDC,		//������ DC
			0, 0,					//������ x,y
			_imageInfo->width,		//������ ����, ����ũ��
			_imageInfo->height,
			_transColor);			//�����Ҷ� ������ Į��
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::rotateRender(HDC hdc, float x, float y, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; ++i)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)* dist);
	}

	if (_trans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			x - _rotateImage->width / 2,
			y - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}
}

void image::rotateFrameRender(HDC hdc, float x, float y, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) *  (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] =  atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	
	for (int i = 0; i < 3; ++i)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) *dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) *dist);
	}

	if (_trans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);

		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1 , RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);

		GdiTransparentBlt(hdc,
			x - _rotateImage->width / 2,
			y - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, _imageInfo->currentFrameX, _imageInfo->currentFrameY, _rotateImage->frameWidth, _rotateImage->frameHeight,  NULL, 0, 0);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� DC
			destX,					//����� ��ǥ X(left)
			destY,					//����� ��ǥ Y(top)
			sourWidth,				//����� ����ũ��
			sourHeight,				//����� ����ũ��
			_imageInfo->hMemDC,		//������ DC
			sourX, sourY,			//������ x,y
			sourWidth,				//������ ����, ����ũ��
			sourHeight,
			_transColor);			//�����Ҷ� ������ Į��
	}
	else
	{
		BitBlt(hdc, destX, destY,
			sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::rotateRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; ++i)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)* dist);
	}

	if (_trans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0,
			0,
			sourWidth,
			sourHeight,
			NULL, 0, 0);
		GdiTransparentBlt(
			hdc,					//����� DC
			destX,					//����� ��ǥ X(left)
			destY,					//����� ��ǥ Y(top)
			sourWidth,				//����� ����ũ��
			sourHeight,				//����� ����ũ��
			_imageInfo->hMemDC,		//������ DC
			sourX, sourY,			//������ x,y
			sourWidth,				//������ ����, ����ũ��
			sourHeight,
			_transColor);			//�����Ҷ� ������ Į��
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

//                    �ѷ���DC    �����̹��� �׷��ٿ���,   ��������X   ��������Y
void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	//������ �����̸� 
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	//ȭ�鿡 �����̹��� �׷��� ���� ����
	int drawAreaX = drawArea->left;						
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;		//�׷��� ����ũ��(Width)
	int drawAreaH = drawArea->bottom - drawAreaY;		//�׷��� ����ũ��(height)

	//���κ��� �غ��ô�
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		//�з��ö� ����
		sourHeight = rcSour.bottom - rcSour.top;

		//ȭ������� �����ٸ�~
		if (y + sourHeight > drawAreaH)
		{
			// - ���궧���� ���� ������ ���� �ݴ�������� �۵��Ѵ�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//ȭ������� ���������� �ٽ� �о�÷��� ��ġ ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ���� ����
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			//���η� ȭ������� ���� ���� ���
			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	if (!_blend) return;
	//������ ������ ��.
	//���� �̹��� �ҽ��� ���ĺ��带 ��������ִ� �Լ�
	//BYTE�� ���ĺ��� ��ġ�ε� 0 ~ 255 (���� �������� ������ ��������)
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//���� ���� ���� �̹����� �����Ѵ�
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

		//Ư�� ������ ������ -> ����Ÿ �� �����ִ� ����
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		//���������� ���ĺ��带 ���δ�
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);
	}

}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blend) return;
	//������ ������ ��.
	//���� �̹��� �ҽ��� ���ĺ��带 ��������ִ� �Լ�
	//BYTE�� ���ĺ��� ��ġ�ε� 0 ~ 255 (���� �������� ������ ��������)
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//���� ���� ���� �̹����� �����Ѵ�
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//Ư�� ������ ������ -> ����Ÿ �� �����ִ� ����
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		//���������� ���ĺ��带 ���δ�
		AlphaBlend(hdc, destX, destY, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);
	}

}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	if (!_blend) return;

	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//���� ���� ���� �̹����� �����Ѵ�
		BitBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			hdc, sourX, sourY, SRCCOPY);

		//Ư�� ������ ������ -> ����Ÿ �� �����ִ� ����
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

		//���������� ���ĺ��带 ���δ�
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			sourWidth, sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourWidth, sourHeight, _blendFunc);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blend) return;

	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//���� ���� ���� �̹����� �����Ѵ�
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight, _imageInfo->frameWidth, _imageInfo->frameHeight, _transColor);

		AlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	if (!_blend) return;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//���� ���� ���� �̹����� �����Ѵ�
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, currentFrameX * _imageInfo->frameWidth, currentFrameY * _imageInfo->frameHeight, _imageInfo->frameWidth, _imageInfo->frameHeight, _transColor);

		AlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth, currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void image::alphaLoopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha)
{
	if (!_blend) return;

	_blendFunc.SourceConstantAlpha = alpha;

	//������ �����̸� 
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	//ȭ�鿡 �����̹��� �׷��� ���� ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;		//�׷��� ����ũ��(Width)
	int drawAreaH = drawArea->bottom - drawAreaY;		//�׷��� ����ũ��(height)

														//���κ��� �غ��ô�
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		//�з��ö� ����
		sourHeight = rcSour.bottom - rcSour.top;

		//ȭ������� �����ٸ�~
		if (y + sourHeight > drawAreaH)
		{
			// - ���궧���� ���� ������ ���� �ݴ�������� �۵��Ѵ�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//ȭ������� ���������� �ٽ� �о�÷��� ��ġ ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ���� ����
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			//���η� ȭ������� ���� ���� ���
			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			alphaRender(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top, alpha);
		}
	}
}

void image::aniRender(HDC hdc, int destX, int destY, animation * ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void image::aniRotateRender(HDC hdc, int destX, int destY, animation * ani, float angle)
{
	rotateRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight() , angle);
}

void image::alphaAniRender(HDC hdc, int destX, int destY, animation * ani, BYTE alpha)
{
	if (!_blend) return;

	_blendFunc.SourceConstantAlpha = alpha;

	alphaRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}
