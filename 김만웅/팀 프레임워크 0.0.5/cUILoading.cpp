#include "stdafx.h"
#include "cUILoading.h"
//
#include "cUIImageView.h"
#include "cUILoadingBar.h"

cUILoading::cUILoading(string sScreen, string sBack, string sFront, D3DXVECTOR3 vPos)
	: m_pUILoadingScreen(NULL)
	, m_pUILoadingBar(NULL)
	, m_fLoading(0.0f)
{
	m_pUILoadingScreen = new cUIImageView(sScreen);
	m_pUILoadingBar = new cUILoadingBar(sBack, sFront, vPos);

	D3DXCreateSprite(_device, &m_pSprite);

	////////////////////////////////////////////////////////////
	//CreateThread(���ڰ�)
	//_In_opt_    LPSECURITY_ATTRIBUTES     lpThreadAttributes,
	//_In_        SIZE_T                    dwStackSize,
	//_In_        LPTHREAD_START_ROUTINE    lpStartAddress,
	//_In_opt_    __drv_aliasesMem LPVOID   lpParameter,
	//_In_        DWORD                     dwCreationFlags,
	//_Out_opt_   LPDWORD					lpThreadId
	///////////////////////////////////////////////////////////

	DWORD dwThID[2];
	CloseHandle(
		CreateThread(
			NULL,	//����Ʈ ���� NULL
			0,		//����Ʈ 0
			(LPTHREAD_START_ROUTINE)ThreadInit,	//�����忡 ���� ȣ��Ǵ� �Լ��� ������
			this,	//�ٷ� �� ���ڰ� ����Ű�� �Լ� ȣ�� ��,������ ���� ����
			NULL/*CREATE_SUSPENDED*/,	//����Ʈ 0
			&dwThID[1])	//������ID �����ϱ� ���� ���� ������
	);
}

cUILoading::~cUILoading()
{
	SAFE_RELEASE(m_pUILoadingScreen);
	SAFE_RELEASE(m_pUILoadingBar);
}

void cUILoading::OnUpdate()
{
	m_pUILoadingBar->OnUpdate();
}

void cUILoading::OnRender()
{
	//EnterCriticalSection(&_cs);
	m_pUILoadingScreen->Render(m_pSprite);
	m_pUILoadingBar->OnRender();
	//LeaveCriticalSection(&_cs);
}

HRESULT cUILoading::ThreadInit(LPVOID lpVod)
{
	return S_OK;
}
