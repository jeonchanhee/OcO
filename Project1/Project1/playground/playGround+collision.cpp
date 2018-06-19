#include "stdafx.h"
#include "playGround.h"

//C++�� �Ѿ���鼭, ��ü������ ����������
//�� ���� ��������� ������ cpp������ ���� �� �ְ� �Ǵµ�
//�������α׷��� ó�� �ڵ差�� ���� �о߿�����
//Ư�� �浹�� ����ؾ��ϴ� ��찡 ���ٺ���
//playGround + init.cpp
//playGround+update.cpp
//playGround+render.cpp

//ó�� �Լ����� cpp�� ���λ��� �ڵ差�� ������
//�������� ���Բ� �ϴ� ����� �����ϴ�
//�˾Ƶθ� ��������, �ǹ����� ���� �ϴ� ��� �� �ϳ�



void playGround::collision()
{
	for (int i = 0; i < _ship->getMinho()->getVMinho().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_em->getVMinion()[j]->getRect(), &_ship->getMinho()->getVMinho()[i].rc))
			{
				_em->removeMinion(j);
				_ship->getMinho()->removeMinho(i);
				break;
			}
		}
	}
}
