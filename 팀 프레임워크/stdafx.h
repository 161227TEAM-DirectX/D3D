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
#include <imm.h>
#pragma comment(lib, "imm32.lib")


// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ ��Ÿ�� ��� �����Դϴ�.
#include <iostream>
#include <fstream>			//��������� ofstream�������� ���

// STL �����̳� �������
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

// DIRECT3D ��� �� ���̺귯�� �߰�
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
//#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")





//====================================================================
//			## ��ũ�λ�� ##
//====================================================================
#define WINNAME (LPTSTR)(TEXT("161227TEAM"))
#define WINSTARTX	150
#define WINSTARTY	30
#define WINSIZEX	1600
#define WINSIZEY	900
#define WINSTYLE	WS_OVERLAPPEDWINDOW

#define STR_LEN 256





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
#define SAFE_release(p)			{if(p) {(p)->release(); (p) = NULL;}}

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
//			## enum ##
//====================================================================
//������ ����Ʈ�� 2���̹Ƿ� �ݵ�� ��弳���� ������ �ٲ�� �Ѵ�.
enum eSelectMode
{
	E_GAME,
	E_MAPTOOL
};

//���̾� ���� Ŭ���� ������ �켱������ �ռ���.
enum eImgLayer
{
	E_NONE,
	E_NONE2,
	E_NONE3
};





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

typedef struct SCENE_VERTEX
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 uv;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
}SCENE_VERTEX, *LPSCENE_VETEX;

typedef struct tagVertexPND
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DCOLOR	color;
	enum{FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE };
}VERTEX_PND, *LPVERTEX_PND;






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

struct ST_DXIMGANI
{
	int nAniIndex;	//�ִϸ��̼� �ε���(��ȣ)
	int nAniCount;	//�ִϸ��̼� ī��Ʈ(�ð�)
	int nAniTime;	//�ִϸ��̼� Ÿ��(����)

	ST_DXIMGANI()
		: nAniIndex(0)
		, nAniCount(0)
		, nAniTime(3) {}
	ST_DXIMGANI(int aniTime)
		: nAniIndex(0)
		, nAniCount(0)
		, nAniTime(aniTime) {}
};





//====================================================================
//			## ���� ����ü ##
//====================================================================

//Terrain ���� ����ü
typedef struct tagTERRAINVERTEX
{
	D3DXVECTOR3 pos;			//��ġ
	D3DXVECTOR3 normal;			//�븻
	D3DXVECTOR3 binormal;		//���̳븻
	D3DXVECTOR3 tangent;		//ź��Ʈ
	D3DXVECTOR2 baseUV;			//0~1 UV
	D3DXVECTOR2 tileUV;			//Ÿ�� UV 
}TERRAINVERTEX, *LPTERRAINVERTEX;

//Terrain �ε��� ����ü ( ��� ����ü �ϳ��� �ﰢ�� �ϳ��� ����Ѵ� )
typedef struct tagTERRAINTRI
{
	DWORD dw0;
	DWORD dw1;
	DWORD dw2;
}TERRAINTRI, *LPTERRAINTRI;

struct ST_MAP
{
	string heightMap;	//���̸� ���
	string splat;		//���÷��� ���
	string tile0;		//Ÿ��0 ���
	string tile1;		//Ÿ��1 ���
	string tile2;		//Ÿ��2 ���
	string tile3;		//Ÿ��3 ���
	vector<D3DXVECTOR3> vecPos;	//���̰�
};






//====================================================================
//			## ���̺걸��ü ## 
//====================================================================

struct tagSaveMap
{
	string infoName;	//�����̸�
	int number;         //���� �ѹ���
	float mapHeight;
};

struct tagSaveObject
{
	string infoName;	//�����̸�
	int objectNumber;   //������Ʈ �ѹ���
	float objectScale;  //������Ʈ ������
	float objectRotate; //������Ʈ �����̼�
	float objectX;      //������Ʈ X
	float objectY;      //������Ʈ Y
	float objectZ;      //������Ʈ Z
};

struct tagSaveCinematic
{
	string infoName;	//�����̸�
	float X;
	float Y;
	float Z;
	float Height;
};

struct tagSaveEndingCinematic
{
	string infoName;	//�����̸�
	float X;
	float Y;
	float Z;
	float rotationX;
	float rotationY;
	float rotationZ;
	int EningNumber;
};

struct tagSaveMonster
{
	string infoName;
	int monsterNumber;
	float monsterX;
	float monsterY;
	float monsterZ;
	float scale;
};

struct tagSaveNode
{
	string infoName;
	int Inumber;
	float nodeX;
	float nodeY;
	float nodeZ;
	int nodeFSSize;
	vector<pair<int, float>> nodeFS;
};

struct tagSaveName
{
	string infoName;	//�����̸�
	string chatName;
	string password;
};





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
#include "cUIObject.h"
#include "cPicking.h"
#include "cRegistBase.h"
//#include "xPlayer.h"
#include "cDxImg.h"
#include "cDxImgButton.h"
#include "cDxImgBar.h"
#include "cDxImgUI.h"
#include "cUIchatting.h"




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
#include "dxParticleTextureManager.h"
#include "dxParticleSystemManager.h"
#include "dxSkillManager.h"
#include "dxEffectManager.h"
#include "soundManager.h"
#include "xPlayerStatus.h"
#include "ActionManager.h"
#include "ioBaseManager.h"
#include "ioSaveManager.h"
#include "ioSaveObjectManager.h"
#include "ioSaveMonsterManger.h"
#include "ioSaveNodeManager.h"
#include "ioHeightManager.h"
#include "ioMapManager.h"
#include "CinematicManger.h"
#include "ioSaveCinemaManger.h"
#include "ioSaveEndingManager.h"
#include "ioSaveNameManager.h"



#include "cObjectManager.h"
#include "cTextureManager.h"
#include "cFilepathManager.h"
#include "cMapManager.h"
#include "cDxImgManager.h"
#include "cDxImgAniManager.h"
#include "cXmeshManager.h"
#include "cUIManager.h"
#include "cStaticMeshManager.h"




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
#define PSM	dxParticleSystemManager::getSingleton()
#define PTM	dxParticleTextureManager::getSingleton()
#define SKM	dxSkillManager::getSingleton()
#define EFFECT dxEffectManager::getSingleton()
#define PLAYERMANAGER xPlayerStatus::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define IOBASEMANAGER ioBaseManager::getSingleton()
#define IOSAVEMANAGER ioSaveManager::getSingleton()
#define IOSAVEOBJECTMANAGER ioSaveObjectManager::getSingleton()
#define IOHEIGHTMANAGER ioHeightManager::getSingleton()
#define IOSAVEMONSTERMANAGER ioSaveMonsterManger::getSingleton()
#define IOSAVENODEMANAGER ioSaveNodeManager::getSingleton()
#define IOMAPMANAGER ioMapManager::getSingleton()
#define IOSAVENAMEMANAGER ioSaveNameManager::getSingleton()
#define IOSAVEENDING ioSaveEndingManager::getSingleton()
#define CINEMATICMANAGER  CinematicManger::getSingleton()
#define IOCINEMATICMANAGER ioSaveCinemaManger::getSingleton()





//====================================================================
//			## �̱���(��ũ��) ##
//====================================================================
// ������ �Ŵ��� Ŭ�������� �ν��Ͻ��� ��´�.





//====================================================================
//			## ���� ##
//====================================================================
#define BLACK	D3DCOLOR_XRGB(0,0,0)
#define RED		D3DCOLOR_XRGB(255,0,0)
#define GREEN	D3DCOLOR_XRGB(0,255,0)
#define BLUE	D3DCOLOR_XRGB(0,0,255)
#define WHITE	D3DCOLOR_XRGB(255,255,255)


#define CRIMSON D3DCOLOR_XRGB(255,187,0)
#define ORANGE	D3DCOLOR_XRGB(255,187,0)
#define YELLOW	D3DCOLOR_XRGB(255,228,0)
#define BROWN	D3DCOLOR_XRGB(117,20,0)
#define GRASS	D3DCOLOR_XRGB(171,242,0)
#define SKY		D3DCOLOR_XRGB(0,216,255)
#define VIOLET	D3DCOLOR_XRGB(95,0,255)
#define PURPLE	D3DCOLOR_XRGB(255,0,221)
#define MAGENTA D3DCOLOR_XRGB(255,0,255)

#define NAMEGREEN D3DCOLOR_XRGB(10, 255,10)
#define NAMEGRAY D3DCOLOR_XRGB(100, 100, 100)
#define NAMERED	D3DCOLOR_XRGB(255,10,10)
#define NAMEPURPLE D3DCOLOR_XRGB(255,0,221)
#define NAMEWHITE D3DCOLOR_XRGB(255,255,255)
#define NAMEPOSITIVE D3DCOLOR_XRGB(190, 10, 10)
#define NAMENEGATIVE D3DCOLOR_XRGB(10, 190, 10)





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
		ACTION_FLY_MOVE_ATT,
		ACTION_FLY_DIE,
		ACTION_LANDING,
		ACTION_REMOVE,
		ACTION_STUN,
		ACTION_DIE,
		ACTION_NONE,
		ACTION_SKILL_TAIL,
		ACTION_SKILL_FIRE,
		ACTION_SKILL_FLY_FIRE,
		ACTION_SKILL_BATTLE_ROAR,
		ACTION_PA_OX
	};

	const float MOVETIME = 1.5f;

	enum FONTCOLOR
	{
		FONT_WHITE = 0,
		FONT_RED,
		FONT_BLUE,
		FONT_GREEN
	};
}




//====================================================================
//			## �������� ## 
//====================================================================
extern HWND				_hWnd;
extern HINSTANCE		_hInstance;
extern float			_timeDelta;
extern CRITICAL_SECTION _cs;
extern D3DVIEWPORT9		leftViewPort;	//���� ����Ʈ
extern D3DVIEWPORT9		rightViewPort;  //������ ����Ʈ
extern eSelectMode		g_eSelectMode;	//���Ӹ������ �����������
extern int forceNumber;