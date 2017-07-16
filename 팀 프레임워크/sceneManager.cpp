#include "stdafx.h"
#include "sceneManager.h"
#include "iGameNode.h"

HRESULT sceneManager::init(void)
{
	return S_OK;
}

void sceneManager::release(void)
{
	//�������� ���
	miSceneList iter = _mSceneList.begin();
	for (; iter != _mSceneList.end();)
	{
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mSceneList.clear();

	//for each(auto p in _mSceneList)
	//{
	//	p.second->release();
	//	SAFE_DELETE(p.second);
	//}
}

void sceneManager::update(void)
{
	//������� �����ϸ� �ش��ϴ� ������� ������Ʈ
	if (_currentScene)
	{
		_currentScene->update();
	}
}

void sceneManager::render(void)
{
	//������� �����ϸ� �ش��ϴ� ������� ������Ʈ
	if (_currentScene)
	{
		_currentScene->render();
	}
}

void sceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (_currentScene)
	{
		_currentScene->WndProc(hWnd, message, wParam, lParam);
	}
}


iGameNode * sceneManager::addScene(string sceneName, iGameNode * scene, bool isSceneChange)
{
	//���� ������ �ΰ� ����
	if (!scene) return NULL;

	//���� ������ �ʿ� ����
	_mSceneList.insert(make_pair(sceneName, scene));

	if (isSceneChange)
		changeScene(sceneName);
	else
		return scene;
}

HRESULT sceneManager::changeScene(string sceneName, bool isFirst)
{
	miSceneList find = _mSceneList.find(sceneName);

	//��ã�Ҵٸ�
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ������� ����?
	if (find->second == _currentScene) return E_FAIL;

	if (isFirst == false)
	{
		//_currentScene->release();
	}

	//������� ������ ���� ������ �� �ʱ�ȭ �ϰ� �������ش�
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}


//#include "gameNode.h"
//HRESULT sceneManager::init(void)
//{
//	return S_OK;
//}
//
//void sceneManager::release(void)
//{
//	//�������� ���
//	miSceneList iter = _mSceneList.begin();
//	for (; iter != _mSceneList.end();)
//	{
//		if (iter->second != NULL)
//		{
//			if (iter->second == _currentScene) iter->second->releaseGameNode();
//			SAFE_DELETE(iter->second);
//			iter = _mSceneList.erase(iter);
//		}
//		else
//		{
//			++iter;
//		}
//	}
//	_mSceneList.clear();
//
//	//for each(auto p in _mSceneList)
//	//{
//	//	p.second->release();
//	//	SAFE_DELETE(p.second);
//	//}
//}
//
//void sceneManager::update(void)
//{
//	//������� �����ϸ� �ش��ϴ� ������� ������Ʈ
//	if (_currentScene)
//	{
//		_currentScene->updateGameNode();
//	}
//}
//
//void sceneManager::render(void)
//{
//	//������� �����ϸ� �ش��ϴ� ������� ������Ʈ
//	if (_currentScene)
//	{
//		_currentScene->renderGameNode();
//	}
//}
//
//gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
//{
//	//���� ������ �ΰ� ����
//	if (!scene) return NULL;
//
//	//���� ������ �ʿ� ����
//	_mSceneList.insert(make_pair(sceneName, scene));
//
//	//���Ŵ��� ���� ����
//	g_eSceneManager = eSceneManager::E_GAMENODE;
//
//	return scene;
//}
//
//HRESULT sceneManager::changeScene(string sceneName)
//{
//	miSceneList find = _mSceneList.find(sceneName);
//
//	//��ã�Ҵٸ�
//	if (find == _mSceneList.end()) return E_FAIL;
//
//	//�ٲٷ��� ���� ������� ����?
//	if (find->second == _currentScene) return E_FAIL;
//
//	//������� ������ ���� ������ �� �ʱ�ȭ �ϰ� �������ش�
//	if (SUCCEEDED(find->second->initGameNode()))
//	{
//		_currentScene = find->second;
//
//		return S_OK;
//	}
//
//	return E_FAIL;
//}