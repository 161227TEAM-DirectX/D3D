#pragma once

class gameNode
{
private:
	typedef struct SCENE_VERTEX 
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR2 uv;
		enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
	}SCENE_VERTEX, *LPSCENE_VETEX;

public:
	camera*					_mainCamera;				//���� ī�޶�

protected:
	LPDIRECT3DCUBETEXTURE9	_environmentTexture;		//ȯ�� �ؽ���
	LPD3DXMESH				_environmemtSphereMesh;		//ȯ�� ���޽�
	LPD3DXEFFECT			_environmentEffect;			//ȯ�� ����Ʈ

	SCENE_VERTEX			_scenePlaneVertex[4];		//����� ���ؽ�
	WORD					_scenePlaneIndex[6];		//����� �ε���
	LPD3DXEFFECT			_postEffect;				//����Ʈ ����Ʈ

	lightDirection*			_sceneBaseDirectionLight;	//���� ��ġ�� �⺻������
	camera*					_directionLightCamera;		//���⼺ ������ ���� ī�޶�
	float					_shadowDistance;			//�׸��� �Ÿ�

public:
	//���ӳ�� ����
	HRESULT initGameNode(void);
	void releaseGameNode(void);
	void updateGameNode(void);
	void renderGameNode(void);

public:
	//�����Լ� �ڽ��ʿ��� ������ �ؼ� ����ϱ�
	virtual HRESULT init(void) = 0;
	virtual void release(void) = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;
	virtual void renderSprite(void) {};

public:
	void setEnvironment(string cubeFilePath);
	void renderEnvironment(void);
	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);
	//����ī�޶��� ���� Texture �� ��´�.
	LPDIRECT3DTEXTURE9 getTexture() { return _mainCamera->getRenderTexture(); }

	//ī�޶� ������Ʈ
	void updateCamera(void);

	gameNode();
	virtual ~gameNode();
};