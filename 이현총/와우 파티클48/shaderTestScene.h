#pragma once
#include "gameNode.h"

class shaderTestScene : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9	_vb;	//정점버퍼
	LPDIRECT3DINDEXBUFFER9	_ib;	//인덱스 버퍼
	camera		_mainCamera;		//메인카메라
	transform	_cubeTrans;			//큐브트렌스
	transform	_lightTrans;		//라이트트렌스


	//이펙트관련 함수(쉐이더)
	LPD3DXEFFECT _effect;			//로딩할 쉐이더
	D3DXHANDLE	 _hTechnique;		//테크닉핸들
	D3DXHANDLE	 _hMatWorld;		//월드행렬핸들
	D3DXHANDLE	 _hMatView;			//뷰행렬핸들
	D3DXHANDLE	 _hMatProjection;	//투영행렬핸들
	D3DXHANDLE	 _hColor;			//컬러정보핸들

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	void CreateCube();
	void RenderCube();

	shaderTestScene() {}
	~shaderTestScene() {}
};

