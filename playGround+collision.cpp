#include "stdafx.h"
#include "playGround.h"

//C++로 넘어오면서, 객체지향이 가능해졌다
//한 개의 헤더파일은 여러개 cpp파일을 가질 수 있게 되는데
//게임프로그래밍 처럼 코드량이 많은 분야에서는
//특히 충돌만 담당해야하는 경우가 많다보니
//playGround + init.cpp
//playGround+update.cpp
//playGround+render.cpp

//처럼 함수별로 cpp를 따로빼서 코드량이 많지만
//가독성을 좋게끔 하는 방법도 가능하다
//알아두면 좋음좋음, 실무에서 많이 하는 방식 중 하나



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
