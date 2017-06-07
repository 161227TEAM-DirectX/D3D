// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//
#pragma once

#include <SDKDDKVer.h>

//#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <Windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ ��Ÿ�� ��� �����Դϴ�.
#include <iostream>
// STL �����̳� �������
#include <string>
#include <vector>
#include <map>
#include <list>
using namespace std;
// DIRECT3D ��� �� ���̺귯�� �߰�
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")




//====================================================================
//			## ���� ���� ��������� �̰��� �߰��Ѵ� ##
//====================================================================
//////////////////////////////////////////////////////////////////////
/*���ӽ����̽� myUtil*/
#include "myUtil.h"
using namespace myUtil;

//////////////////////////////////////////////////////////////////////
/*�Ϲ� Ŭ����*/
#include "transform.h"
#include "camera.h"
#include "lightDirection.h"
#include "lightPoint.h"
#include "boundBox.h"

//////////////////////////////////////////////////////////////////////
/*�̱��� �Ŵ��� Ŭ����*/
#include "keyManager.h"
#include "timeManager.h"
#include "sceneManager.h"
#include "fontManager.h"
#include "gizmoManager.h"
#include "cameraManager.h"
#include "rmTexture.h"
#include "rmShaderFX.h"
#include "rmStaticMesh.h"
#include "rmSkinnedMesh.h"
#include "physicsManager.h"
#include "spriteManager.h"
#include "dxParticleSystemManager.h"

//====================================================================
//			## �̱����� �̰��� �߰��Ѵ� ##
//====================================================================
#define _device	device
#define KEYMANAGER keyManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define FONTMANAGER fontManager::getSingleton()
#define GIZMOMANAGER gizmoManager::getSingleton()
#define RM_TEXTURE rmTexture::getSingleton()
#define RM_SHADERFX rmShaderFX::getSingleton()
#define RM_XMESH rmStaticMesh::getSingleton()
#define RM_SKINNED rmSkinnedMesh::getSingleton()
#define PHYSICSMANAGER physicsManager::getSingleton()
#define SPRITEMANAGER spriteManager::getSingleton()
#define PSM	dxParticleSystemManager::getSingleton()

//====================================================================
//			## �����ι� - ��ũ�� ## (������â �ʱ�ȭ)
//====================================================================
#define WINNAME (LPTSTR)(TEXT("UI"))
#define WINSTARTX		050
#define WINSTARTY		050
#define WINSIZEX		1600
#define WINSIZEY		900
#define WINSTYLE		WS_OVERLAPPEDWINDOW

//====================================================================
//			## ��ũ���Լ� ## (Ŭ���� �����Ҵ�� �κ� ����)
//====================================================================
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[] (p); (p) = NULL;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->Release(); (p) = NULL;}}

//====================================================================
//			## �������� ## 
//====================================================================
extern HWND _hWnd;
extern HINSTANCE _hInstance;
extern float _timeDelta;

//====================================================================
//			## FVF ## (���� �ϳ��� ���� ������ �����ϴ� ����ü)
//====================================================================


typedef struct tagVertex
{
	D3DXVECTOR3 pos;		//������ ��ġ
	DWORD		color;		//������ �÷�

	//���� ������ ������ ��Ÿ���� �÷��� �����
	//D3DFVF_XYZ ������ ��ġ����
	//D3DFVF_DIFFUSE ������ �÷�����
	tagVertex() {}
	tagVertex(D3DXVECTOR3 p, D3DCOLOR c) : pos(p), color(c) {}
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
}MYVERTEX, *LPMYVERTEX;

typedef struct tagVertexPN
{
	D3DXVECTOR3 pos;		//������ ��ġ
	D3DXVECTOR3 normal;		//������ �븻 ����(���� ǥ���� �ٶ󺸴� ������ ��´�)
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
}MYVERTEX_PN, *LPMYVERTEX_PN;

typedef struct tagVertexPU
{
	D3DXVECTOR3 pos;		//������ ��ġ
	D3DXVECTOR2	uv;			//������ UV��ǥ (0.0f ~ 1.0f)
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
}MYVERTEX_PU, *LPMYVERTEX_PU;
