#include "stdafx.h"
#include "keyManager.h"

HRESULT keyManager::init()
{
	//키값을 전부 눌려 있지 않은 상태로 초기화 한다
	for (int i = 0; i < KEYMAX; i++)
	{
		for (int j=0; j < KEYSAME; j++)
		{
			_keyUp[i][j] = false;
			_keyDown[i][j] = false;
		}
	}

	return S_OK;
}

void keyManager::release(void)
{
}

bool keyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		for (int i=0; i < KEYSAME; i++)
		{
			if (!_keyDown[key][i])
			{
				_keyDown[key][i] = true;
				return true;
			}
			break;
		}
	}
	else
	{
		for (int i=0; i < KEYSAME; i++)
		{
			_keyDown[key][i] = false;
		}
	}

	return false;
}

bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		for (int i=0; i < KEYSAME; i++)
		{
			_keyUp[key][i] = true;
		}
	}
	else
	{
		for (int i=0; i < KEYSAME; i++)
		{
			if (_keyUp[key][i])
			{
				_keyUp[key][i] = false;
				return true;
			}
		}
	}

	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}
