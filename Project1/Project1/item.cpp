#include "item.h"
#include <iostream>
#include <string>

using namespace std;



item::item()
{
	string hi;
	cout << " 민호 : 안녕하세요 여러분 " << endl;
	cout << " 민호의 인사를 받아주세요" << endl;
	cin >> hi;
	
	cout << "이걸 안받아줘 버리나 ??" << endl;

}


item::~item()
{
}
