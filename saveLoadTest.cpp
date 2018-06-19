#include "stdafx.h"
#include "saveLoadTest.h"


saveLoadTest::saveLoadTest()
{
}


saveLoadTest::~saveLoadTest()
{

}

void saveLoadTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) save();
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) load();
}

void saveLoadTest::save()  
{
	//파일 입출력
	// C - FILE*    기능은적으나 빠름
	// C++ - ifstream, ofstream 기능은 많으나 그만큼 느림
	// WIN32 - CreateFile()

	HANDLE file;
	DWORD write;

	char str[128] = "쌤은 또 생각해보라고 그러실거잖아요";

	file = CreateFile("10기의마들.txt", GENERIC_WRITE, FALSE,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);

}

void saveLoadTest::load()  
{
	HANDLE file;
	DWORD read;

	char str[128];

	file = CreateFile("10기의마들.txt", GENERIC_READ, FALSE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);

	MessageBox(_hWnd, str, "담주 슈팅 홧팅!", MB_YESNOCANCEL);
}
