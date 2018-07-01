#include "stdafx.h"
#include "DialogTraining.h"


DialogTraining::DialogTraining() {}
DialogTraining::~DialogTraining() {}

HRESULT DialogTraining::init()
{
	Dialog::init();

	_ansBack = new image;
	_ansBack->init("image/UI/UIdias(400x250).bmp", 400, 320, true, RGB(255, 0, 255));

	_name = "ī��κ�";
	_training = TRAINING_RESCUE;

	_vButton.resize(4);
	_vButtonDialog.resize(4);
	_vDialog.resize(5);

	for (int i = 0; i < _vButton.size(); i++)
	{
		_vButton[i] = RectMake(WINSIZEX - 180, WINSIZEY - 600 + i * 50, 200, 50);
	}
	_vButtonDialog[0] = "�Ʒ���";
	_vButtonDialog[1] = "�̾߱��ϱ�";
	_vButtonDialog[2] = "�ʱ�ȭ";
	_vButtonDialog[3] = "�ƹ��͵�";

	setDialog();
	return S_OK;
}

void DialogTraining::release()
{

}

void DialogTraining::update()
{
	keyControl();
	clickButton();
	setFrame();
}

void DialogTraining::render()
{
	Dialog::render();

	_ansBack->render(DC, WINSIZEX - 200, WINSIZEY - 650);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			Rectangle(DC, _vButton[i].left, _vButton[i].top, _vButton[i].right, _vButton[i].bottom);
		}
	}

	HFONT font, oldFont;
	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("�Ҿ߹ٸ�9"));
	oldFont = (HFONT)SelectObject(DC, font);
	SetTextColor(DC, RGB(255, 255, 255));
	SetBkMode(DC, TRANSPARENT);
	if ((int)_training == 4 && _idY == 1)
		DrawText(DC, _vDialog[4][0].c_str(), strlen(_vDialog[4][0].c_str()), &_rc[1], DT_VCENTER);
	string str = _vDialog[(int)_training][_idY].substr(0, _idX);
	if ((int)_training == 4 && _idY == 1)
		DrawText(DC, str.c_str(), strlen(str.c_str()), &_rc[2], DT_VCENTER);
	else
		DrawText(DC, str.c_str(), strlen(str.c_str()), &_rc[1], DT_VCENTER);
	SelectObject(DC, oldFont);
	DeleteObject(font);

	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("�Ҿ߹ٸ�9"));
	oldFont = (HFONT)SelectObject(DC, font);
	for (int i = 0; i < _vButton.size(); i++)
	{
		DrawText(DC, _vButtonDialog[i].c_str(), strlen(_vButtonDialog[i].c_str()), &_vButton[i], DT_VCENTER | DT_CENTER);
	}
	SelectObject(DC, oldFont);
	DeleteObject(font);
}

void DialogTraining::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&_uiBack->boundingBox(), _ptMouse))
	{
		//changeDialog();
		if (_idX < _vDialog[(int)_training][_idY].size() - 1)
			_idX = _vDialog[(int)_training][_idY].size() - 1;
		else if ((_idY + 1) < _vDialog[(int)_training].size())
		{
			_idY++;
			_idX = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		changeDialog();
	}
}

void DialogTraining::setFrame()
{
	_count++;

	if (!(_count % 3))
	{
		_count = 0;
		if (_idX < _vDialog[(int)_training][_idY].size())
		{
			_idX++;
		}
	}
}

void DialogTraining::setDialog()
{
	switch (_training)
	{
	case TRAINING_RESCUE:
		if (_vDialog[0].size() == 0) _vDialog[0].resize(2);
		else return;
		_vDialog[0][0] = "�ڳ״�..���谡�ΰ�? ������ ��� �Ʒ��� �ϸ鼭 �ڳװ��� ���谡�� ���� ������.";
		_vDialog[0][1] = "�� �����... �����غ��� �׷� ����� �־���. �ϴ� �������� ������ ����!";
	break;
	case TRAINING_AFTER_RESCUE:
		if (_vDialog[1].size() == 0) _vDialog[1].resize(5);
		else return;
		_vDialog[1][0] = "����! ����!";
		_vDialog[1][1] = "���ݱ��� ���������� ������ �ٳ༭ �����ҰǸ�..!";
		_vDialog[1][2] = "�ּ��ּ� (�ٱ�ٱ��� ������ ���´�. ������ �Ųٷ� ���� �ִ� �� ����)";
		_vDialog[1][3] = "�̰��� ���� ������ �׷��� �ϴ°�. �� ��, �� �̸��� ī��κ�.";
		_vDialog[1][4] = "�� �������� ���� ������ �Ʒ��� �ð� ����. �� ��Ź�ϳ�!";
	break;
	case TRAINING_BUILD:
		if (_vDialog[2].size() == 0) _vDialog[2].resize(2);
		else return;
		_vDialog[2][0] = "�Ʒ����� �����ᱺ! ����!";
		_vDialog[2][1] = "�ڳ��� �ɷ��� �Ʒ��ϰ� ������ �������� ���Է� ���Գ�. ���� ���ʿ� ������!";
	break;
	case TRAINING_BUILDING:
		if (_vDialog[3].size() == 0) _vDialog[3].resize(1);
		else return;
		_vDialog[3][0] = "�ڳ� �Ա�! �Ʒ��� �ٰ�?";
	break;
	case TRAINING_DIALOG:
		if (_vDialog[4].size() == 0) _vDialog[4].resize(3);
		else return;
		_vDialog[4][0] = "������Կ��� ���������, �ǹ����� ���� �ִ� �ڸ��� �ٽ� �����޶�� ������ȴµ�,";
		_vDialog[4][1] = "�����ϼ̳�.";
		_vDialog[4][2] = "����ϴ� ������� �ٸ� ���� �������� �ʹٳ�..�Ʒ��常�� ���� ��ġ �״�ζ��.";
	break;
	}
}

void DialogTraining::changeDialog()
{
	switch (_training)
	{
	case TRAINING_RESCUE:
		_training = TRAINING_AFTER_RESCUE;
		break;
	case TRAINING_AFTER_RESCUE:
		_training = TRAINING_BUILD;
		break;
	case TRAINING_BUILD:
		_training = TRAINING_BUILDING;
		break;
	case TRAINING_DIALOG:
		_training = TRAINING_AFTER_RESCUE;
		break;
	}
	_count = _idX = _idY = 0;
	setDialog();
}
void DialogTraining::clickButton()
{
	if (_training != TRAINING_BUILDING) return;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i], _ptMouse))
			{
				if (i == 1)
				{
					_training = TRAINING_DIALOG;
					_count = _idX = _idY = 0;
					setDialog();
				}
			}
		}
	}
}