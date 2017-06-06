#include "stdafx.h"
#include "testScene.h"


testScene::testScene()
{
}


testScene::~testScene()
{
}

HRESULT testScene::init()
{
	//임계 영역 오브젝트를 초기화한다.
	InitializeCriticalSection(&_cs);

	DWORD dwThID[2];
	CloseHandle(CreateThread(
		NULL,	//스레드 커널 오브젝트 보안 특성 기본 NULL
		0,		//스레드 스택 크기 디폴트 '0'
		(LPTHREAD_START_ROUTINE)ThreadSetup,	//실행되는 함수
		this,	//실행되는 함수에 넘겨지는 매개변수
		NULL/*CREATE_SUSPENDED*/,	//스레드 제어하는 플래그
		&dwThID[1]));				//스레드의 ID값

	return S_OK;
}

void testScene::release()
{
}

void testScene::update()
{
}

void testScene::render()
{
	EnterCriticalSection(&_cs);		//사용
	//이 사이에 렌더(멀티스레드)
	LeaveCriticalSection(&_cs);		//사용 끝
}

void testScene::ThreadSetup(LPVOID lpVod)
{
}
