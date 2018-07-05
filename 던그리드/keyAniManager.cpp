#include "stdafx.h"
#include "keyAniManager.h"
#include "image.h"
#include "animation.h"

keyAniManager::keyAniManager()
{
}


keyAniManager::~keyAniManager()
{
}

HRESULT keyAniManager::init()
{
	return S_OK;
}

void keyAniManager::release()
{
}

void keyAniManager::update()
{
	/*iterAnimation iter = _mTotalAnimation.begin();

	for (iter; iter != _mTotalAnimation.end(); ++iter)
	{
		if (!iter->second->isPlay()) continue;

		iter->second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
	}*/
	iterTotalAnimation  vIter;

	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		iterAnimation iter = vIter->begin();

		for (iter; iter != vIter->end(); ++iter)
		{
			if (!iter->second->isPlay()) continue;

			iter->second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
		}
	}
}

void keyAniManager::render()
{
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop)
{
	arrAnimation mArrAnimation;

	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	mArrAnimation.insert(pair<string, animation*>(animationKeyName, ani));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction)
{
	arrAnimation mArrAnimation;

	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	mArrAnimation.insert(pair<string, animation*>(animationKeyName, ani));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction, void * obj)
{
	arrAnimation mArrAnimation;

	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	mArrAnimation.insert(pair<string, animation*>(animationKeyName, ani));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop)
{
	arrAnimation mArrAnimation;

	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop);
	ani->setFPS(fps);

	mArrAnimation.insert(pair<string, animation*>(animationKeyName, ani));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction)
{
	arrAnimation mArrAnimation;

	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	mArrAnimation.insert(pair<string, animation*>(animationKeyName, ani));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction, void * obj)
{
	arrAnimation mArrAnimation;

	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	mArrAnimation.insert(pair<string, animation*>(animationKeyName, ani));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop)
{
	arrAnimation mArrAnimation;

	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	mArrAnimation.insert(pair<string, animation*>(animationKeyName, ani));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction)
{
	arrAnimation mArrAnimation;

	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	mArrAnimation.insert(pair<string, animation*>(animationKeyName, ani));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction, void * obj)
{
	arrAnimation mArrAnimation;

	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	mArrAnimation.insert(pair<string, animation*>(animationKeyName, ani));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::start(string animationKeyName)
{
	iterTotalAnimation vIter;
	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		iterAnimation iter = vIter->find(animationKeyName);

		iter->second->start();
	}
}

void keyAniManager::stop(string animationKeyName)
{
	iterTotalAnimation vIter;
	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
	iterAnimation iter = vIter->find(animationKeyName);

	iter->second->stop();
	}
}

void keyAniManager::pause(string animationKeyName)
{
	iterTotalAnimation vIter;
	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		iterAnimation iter = vIter->find(animationKeyName);

		iter->second->pause();
	}
}

void keyAniManager::resume(string animationKeyName)
{
	iterTotalAnimation vIter;
	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
	iterAnimation iter = vIter->find(animationKeyName);

	iter->second->resume();
	}
}

animation * keyAniManager::findAnimation(string animationKeyName)
{
	iterTotalAnimation vIter;
	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
	iterAnimation iter = vIter->find(animationKeyName);

	if (iter != vIter->end())
	{
		return iter->second;
	}
	}
	return NULL;
}

void keyAniManager::deleteAll()
{
	iterTotalAnimation vIter;
	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		iterAnimation iter = vIter->begin();
		for (; iter != vIter->end();)
		{
			if (iter->second != NULL)
			{
				iter->second->release();
				SAFE_DELETE(iter->second);
				iter = vIter->erase(iter);
			}
			else ++iter;
		}
		vIter->clear();
	}
	_vTotalAnimation.clear();
}
