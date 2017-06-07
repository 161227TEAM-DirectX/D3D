// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once

#include <SDKDDKVer.h>

//#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <Windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ 런타임 헤더 파일입니다.
#include <iostream>
// STL 컨테이너 헤더파일
#include <string>
#include <vector>
#include <map>
#include <list>
using namespace std;
// DIRECT3D 헤더 및 라이브러리 추가
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")




//====================================================================
//			## 내가 만든 헤더파일을 이곳에 추가한다 ##
//====================================================================
//////////////////////////////////////////////////////////////////////
/*네임스페이스 myUtil*/
#include "myUtil.h"
using namespace myUtil;

//////////////////////////////////////////////////////////////////////
/*일반 클래스*/
#include "transform.h"
#include "camera.h"
#include "lightDirection.h"
#include "lightPoint.h"
#include "boundBox.h"

//////////////////////////////////////////////////////////////////////
/*싱글톤 매니져 클래스*/
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
//			## 싱글톤을 이곳에 추가한다 ##
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
//			## 디파인문 - 메크로 ## (윈도우창 초기화)
//====================================================================
#define WINNAME (LPTSTR)(TEXT("UI"))
#define WINSTARTX		050
#define WINSTARTY		050
#define WINSIZEX		1600
#define WINSIZEY		900
#define WINSTYLE		WS_OVERLAPPEDWINDOW

//====================================================================
//			## 메크로함수 ## (클래스 동적할당된 부분 해제)
//====================================================================
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[] (p); (p) = NULL;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->Release(); (p) = NULL;}}

//====================================================================
//			## 전역변수 ## 
//====================================================================
extern HWND _hWnd;
extern HINSTANCE _hInstance;
extern float _timeDelta;

//====================================================================
//			## FVF ## (정점 하나에 대한 정보를 정의하는 구조체)
//====================================================================


typedef struct tagVertex
{
	D3DXVECTOR3 pos;		//정점의 위치
	DWORD		color;		//정점의 컬러

	//현재 정점의 정보를 나타내는 플래그 상수값
	//D3DFVF_XYZ 정점의 위치정보
	//D3DFVF_DIFFUSE 정점의 컬러정보
	tagVertex() {}
	tagVertex(D3DXVECTOR3 p, D3DCOLOR c) : pos(p), color(c) {}
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
}MYVERTEX, *LPMYVERTEX;

typedef struct tagVertexPN
{
	D3DXVECTOR3 pos;		//정점의 위치
	D3DXVECTOR3 normal;		//정점의 노말 벡터(정점 표면의 바라보는 방향을 얻는다)
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
}MYVERTEX_PN, *LPMYVERTEX_PN;

typedef struct tagVertexPU
{
	D3DXVECTOR3 pos;		//정점의 위치
	D3DXVECTOR2	uv;			//정점의 UV좌표 (0.0f ~ 1.0f)
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
}MYVERTEX_PU, *LPMYVERTEX_PU;
