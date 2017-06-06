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
	//�Ӱ� ���� ������Ʈ�� �ʱ�ȭ�Ѵ�.
	InitializeCriticalSection(&_cs);

	DWORD dwThID[2];
	CloseHandle(CreateThread(
		NULL,	//������ Ŀ�� ������Ʈ ���� Ư�� �⺻ NULL
		0,		//������ ���� ũ�� ����Ʈ '0'
		(LPTHREAD_START_ROUTINE)ThreadSetup,	//����Ǵ� �Լ�
		this,	//����Ǵ� �Լ��� �Ѱ����� �Ű�����
		NULL/*CREATE_SUSPENDED*/,	//������ �����ϴ� �÷���
		&dwThID[1]));				//�������� ID��

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
	EnterCriticalSection(&_cs);		//���
	//�� ���̿� ����(��Ƽ������)
	LeaveCriticalSection(&_cs);		//��� ��
}

void testScene::ThreadSetup(LPVOID lpVod)
{
}
