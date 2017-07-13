#pragma once
#include "iGameNode.h"
class mapObject;
class Environment;
class WaterTerrain;
class monster;
class cUIPlayer;

class stageTwo :	public iGameNode
{
private:
	camera* _mainCamera;						//����ī�޶�
	camera* _directionLightCamera;				//��ī�޶�
	lightDirection* sceneBaseDirectionLight;	//���⺻��

	xPlayer* player;							//�÷��̾�
	mapObject* objectSet;						//����������Ʈ ���� Ŭ����

	terrain*			_terrain;				//����Ŭ����
	terrain*			_terrainShadow;			//���� �׸���
	Environment*		env;					//ȯ��� ����
	WaterTerrain*		water;					//������ ����
	dx::transform*		toRotate;			//�¾� ��������

	baseObject*			_gate1;
	baseObject*			_gate2;
private:
	vector<baseObject*> _renderObject;			//����� ������Ʈ ����
	vector<baseObject*>	_cullObject;			//�������� �ø��� ������Ʈ ����
	vector<monster*> _monsterRegion;
	D3DXMATRIX matRotate;
private:
	float _shadowDistance;
	float currTime;
	int angleZ;
	tagSaveMap envTemp;
	tagSaveMap waterTemp;

private:
	cUIPlayer* m_pUIPlayer;

public:
	stageTwo() { clear(); }
	~stageTwo() { destroy(); }

	HRESULT clear(void);
	void destroy(void);

	HRESULT init();
	void release();
	void update();
	void render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//�׸��ڸ� ���� �ʱ�ȭ �۾� ����
	void shadowInit(void);
	//�׸��� ������Ʈ
	void shadowUpdate(void);
	//�׸��� ����
	void shadowRender(void);

	void loadMonster(void);
	void loadNode(void);

	xMesh* findMonster(int&);
	string findMonsterName(int&);

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);

	void sceneChange();
};

