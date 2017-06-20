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
};

class leftViewHead : public iGameNode
{
private:
	
	rightView*        _rightView;		//����Ʈ��Ŭ����
	terrainSc*		  _terrainSc;		//����Ŭ����
	terrain*		  _terrain;			//����Ŭ����
	Environment*	  _environment;		//ȯ���Ŭ����
	lightDirection*	  _directionLight;	//��Ŭ����
	mapObject*        _mapObject;		//�ʿ�����Ʈ
	WaterTerrain*	  _waterTerrain;    //���� ������Ʈ
	camera			  _mainCamera;

	lightDirection*			_sceneBaseDirectionLight;	//���� ��ġ�� �⺻������

private:
	D3DXVECTOR3		_hitPos;	    //��Ʈ ������
	bool			_isCheck;	    //��Ʈ ����
	POINT _ptMousePos;              //�����닚���� ���� ����Ʈ ���콺����
	Ray ray;                        //��ŷ����

private:
	vector<baseObject*>	m_vecObject;//������Ʈ push_back ���� ����
	float matScaleNumber;           //ũ�⸦ ���� ����
	float mapRotation;

	//�ʹ���
	LEFTVIEWUI _leftView;

	//������Ʈ�� ���� save
	vector<tagSaveObject> InfoObjectTemp;
	tagSaveObject ObjecTemp;

private:
	int co;
	enum eHeightType { E_NONE, E_UP, E_DOWN };
	eHeightType m_eHeightType;			//���̰��� �ø����� ���������� ������ ����ִ�.

	char* tile1;
	char* tile2;
	char* tile3;
	char* tile4;
	char* splat;
	char* raw;

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
	void Load();

	void render();
	void setLink(rightView* rightView) { _rightView = rightView; }
};

