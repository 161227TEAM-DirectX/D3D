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
	camera*					_mainCamera;				//메인 카메라

protected:
	LPDIRECT3DCUBETEXTURE9	_environmentTexture;		//환경 텍스쳐
	LPD3DXMESH				_environmemtSphereMesh;		//환경 구메시
	LPD3DXEFFECT			_environmentEffect;			//환경 이펙트

	SCENE_VERTEX			_scenePlaneVertex[4];		//씬평면 버텍스
	WORD					_scenePlaneIndex[6];		//씬평면 인덱스
	LPD3DXEFFECT			_postEffect;				//포스트 이펙트

	lightDirection*			_sceneBaseDirectionLight;	//씬에 배치된 기본라이팅
	camera*					_directionLightCamera;		//방향성 광원에 따른 카메라
	float					_shadowDistance;			//그림자 거리

public:
	//게임노드 세팅
	HRESULT initGameNode(void);
	void releaseGameNode(void);
	void updateGameNode(void);
	void renderGameNode(void);

public:
	//가상함수 자식쪽에서 재정의 해서 사용하기
	virtual HRESULT init(void) = 0;
	virtual void release(void) = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;
	virtual void renderSprite(void) {};

public:
	void setEnvironment(string cubeFilePath);
	void renderEnvironment(void);
	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);
	//메인카메라의 랜더 Texture 를 얻는다.
	LPDIRECT3DTEXTURE9 getTexture() { return _mainCamera->getRenderTexture(); }

	//카메라 업데이트
	void updateCamera(void);

	gameNode();
	virtual ~gameNode();
};