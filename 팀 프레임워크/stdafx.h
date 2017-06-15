// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//
#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

// Windows ��� ����:
#include <Windows.h>
#include <assert.h>

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
#include <set>
#include <queue>
using namespace std;

// DIRECT3D ��� �� ���̺귯�� �߰�
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")



//====================================================================
//			## ��ũ���Լ� ##
//====================================================================
#define SINGLETONE(class_name) private:\
	class_name(void);\
	~class_name(void);\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

#define SINGLETWO(class_name)\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->Release(); (p) = NULL;}}
#define SAFE_ADD_REF(p)			{if(p) {p->AddRef();}}

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_ONLY_GETTER(varType, varName, FunName)\
protected: varType varName;\
public: inline varType Get##FunName(void) { return varName; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(varType& var){ varName = var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) { return varName; }\
public: virtual void Set##funName(varType var){\
	if (varName != var) {\
	SAFE_ADD_REF(var);\
	SAFE_RELEASE(varName);\
	varName = var;\
		}\
	}




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
#include "terrain.h"
#include "cObject.h"
#include "cPicking.h"




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
#include "ioBaseManager.h"
#include "dxParticleSystemManager.h"

#include "cObjectManager.h"
#include "cTextureManager.h"
#include "ActionManager.h"

//====================================================================
//			## �̱���(���) ##
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
#define IOBASEMANAGER ioBaseManager::getSingleton()
#define PSM	dxParticleSystemManager::getSingleton()


//====================================================================
//			## �̱���(��ũ��) ##
//====================================================================
// ������ �Ŵ��� Ŭ�������� �ν��Ͻ��� ��´�.




//====================================================================
//			## �����ι� - ��ũ�� ## (������â �ʱ�ȭ)
//====================================================================
#define WINNAME (LPTSTR)(TEXT("161227TEAM"))
#define WINSTARTX	150
#define WINSTARTY	30
#define WINSIZEX	1600
#define WINSIZEY	900
#define WINSTYLE	WS_OVERLAPPEDWINDOW





//====================================================================
//			## �������� ## 
//====================================================================
extern HWND				_hWnd;
extern HINSTANCE		_hInstance;
extern float			_timeDelta;
extern CRITICAL_SECTION _cs;

namespace LHS
{
	enum ACTIONRESULT
	{
		ACTION_FINISH = 0,
		ACTION_FAIL,
		ACTION_PLAY,
		ACTION_STAND,
		ACTION_ATT,
		ACTION_MOVE,
		ACTION_FLY,
		ACTION_REMOVE,
		ACTION_STUN,
		ACTION_DIE,
		ACTION_NONE,
		ACTION_SKILL_TAIL,
		ACTION_SKILL_FIRE,
		ACTION_SKILL_FLY_FIRE,
		ACTION_SKILL_BATTLE_ROAR
		//BOSSAC_FINISH,
		//BOSSAC_FAIL,
		//BOSSAC_PLAY,
		//BOSSAC_STAND,
		//BOSSAC_ATT,
		//BOSSAC_SKILL,
		//BOSSAC_MOVE,
		//BOSSAC_REMOVE,
		//BOSSAC_DIE,
		//BOSSAC_NONE
	};

	enum BOSSACTIONRESULT
	{
		
	};

	const float MOVETIME = 1.5f;
}

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

struct ST_RHWC_VERTEX
{
	D3DXVECTOR4 p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
};




//====================================================================
//			## ����ü ##
//====================================================================
struct ST_SIZEF
{
	float fWidth;
	float fHeight;
	ST_SIZEF() : fWidth(0.0f), fHeight(0.0f) {}
	ST_SIZEF(float _fWidth, float _fHeight) : fWidth(_fWidth), fHeight(_fHeight) {}
};
