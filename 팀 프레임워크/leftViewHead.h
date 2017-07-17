#pragma once
#include "iGameNode.h"
//
class terrain;
class terrainSc;
class Environment;
class mapObject;
class WaterTerrain;
class rightView;

struct LEFTVIEWUI
{
	LPDIRECT3DTEXTURE9 tex;
	RECT rc1, rc2, rc3;
	bool FT;
};

class leftViewHead : public iGameNode
{
private:
	rightView*			_rightView;			//����Ʈ��Ŭ����
	terrainSc*			_terrainSc;			//����Ŭ����
	terrain*			_terrain;			//����Ŭ����
	Environment*		_environment;		//ȯ���Ŭ����
	lightDirection*		_directionLight;	//��Ŭ����
	mapObject*			_mapObject;			//�ʿ�����Ʈ
	WaterTerrain*		_waterTerrain;		//���� ������Ʈ
	camera*				_mainCamera;		//�׷�

	vector<baseObject*>	_monster;

	lightDirection*		_sceneBaseDirectionLight;	//���� ��ġ�� �⺻������

private:
	D3DXVECTOR3		_hitPos;	    //��Ʈ ������
	bool			_isCheck;	    //��Ʈ ����
	POINT _ptMousePos;              //�����닚���� ���� ����Ʈ ���콺����
	Ray ray;                        //��ŷ����

private:
	vector<baseObject*>	m_vecObject;//������Ʈ push_back ���� ����
	float matScaleNumber;           //ũ�⸦ ���� ����
	float mapRotation;
	int   NumberCount;
	//�ʹ���
	LEFTVIEWUI _leftView;
	LEFTVIEWUI _SaveButton;
	LEFTVIEWUI _LoadButton;

	//������Ʈ�� ���� save
	vector<tagSaveObject> InfoObjectTemp;
	tagSaveObject ObjecTemp;

	//������ ����
	D3DXVECTOR2		m_vSelectIdx;

private:
	enum eHeightType { E_NONE, E_UP, E_DOWN };
	eHeightType m_eHeightType;			//���̰��� �ø����� ���������� ������ ����ִ�.

	char* tile1;
	char* tile2;
	char* tile3;
	char* tile4;
	char* splat;
	char* raw;

	int sour;
	int dest;
	bool first;
	//LOAD�κ�

private:
	tagSaveObject object;
	//�ؽ���ĥ�ϴºκ�
private:
	D3DXVECTOR3		m_vCSelectRangePos;
	string			m_sCCurTex;
	D3DXVECTOR3		m_vCSelectPos;
	D3DXVECTOR3		m_vCSelectColor;
	D3DXVECTOR2		m_vCSelectIdx;
	LPDIRECT3DTEXTURE9 m_pCSplatBase;

	int m_nSplatRange;		//��ĥ ����

	LEFTVIEWUI _textureColorBack;   //�޹��
	LEFTVIEWUI _textureColorMix[4];    //���� ��ư
	LEFTVIEWUI _textureColorMixSize[4];//���� ������

	pair <bool, POINT> _pick1;
	pair <bool, POINT> _pick2;

	enum MOVETYPE { BackRight = 1, BackLeft = 2, RightSTOP = 3, LeftSTOP = 4 };
	int MoveX, MAXX;
	int MoveY, MAXY;


public:
	leftViewHead();
	~leftViewHead();

	HRESULT init();

	void release();

	void update();
	void PickUdate();
	void terrainUpdate();
	void terrainTextureUpate();
	void monsterMaptul();
	void save();

	//ĥ�ϴ� �κ� �Լ�
	void textureColorInit();
	void textureColorUpdate();
	void textureColorRender();

	void render();
	void setLink(rightView* rightView) { _rightView = rightView; }

	void monsterSelect(string str, int monsterNumber);
	void loadMonster(void);

	xMesh* findMonster(int&);
	string findMonsterName(int&);

	void loadNode(void);
};