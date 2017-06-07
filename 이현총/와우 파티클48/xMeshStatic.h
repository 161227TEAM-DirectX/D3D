#pragma once
#include "xMesh.h"

class xMeshStatic : public xMesh
{
public:
	static LPD3DXEFFECT				_staticMeshEffect;	//고정메시를 그리는 이펙트
	static LPDIRECT3DTEXTURE9		_defDiffuseTex;		
	static LPDIRECT3DTEXTURE9		_defNormalTex;
	static LPDIRECT3DTEXTURE9		_defSpecularTex;
	static LPDIRECT3DTEXTURE9		_defEmissionTex;

public:
	LPD3DXMESH						_mesh;

	DWORD							_materialsNum;		//로딩된 매쉬의 재질 갯수
	vector<LPDIRECT3DTEXTURE9>		_vecDiffuseTex;		//로딩된 메쉬에서 사용하는 DiffuseTexture
	vector<LPDIRECT3DTEXTURE9>		_vecNormalTex;		//로딩된 메쉬에서 사용하는 NormalTexture
	vector<LPDIRECT3DTEXTURE9>		_vecSpecularTex;	//로딩된 메쉬에서 사용하는 SpecularTexture
	vector<LPDIRECT3DTEXTURE9>		_vecEmissionTex;	//로딩된 메쉬에서 사용하는 EmissionTexture
	vector<D3DMATERIAL9>			_vecMaterials;		//로딩된 메쉬에서 사용하는 매터리얼

	vector<D3DXVECTOR3>				_vertices;			//정점들
	vector<D3DXVECTOR3>				_normals;			//점정노말
	vector<DWORD>					_indices;			//인덱스
	DWORD							_triNum;			//삼각면의 갯수

public:
	D3DXVECTOR3						_boundMin;			//바운드의 최소 위치 
	D3DXVECTOR3						_boundMax;			//바운드의 최대 위치 
	D3DXVECTOR3						_boundCenter;		//바운드의 센터 (주의사항 피봇이 아니다)
	D3DXVECTOR3						_boundSize;			//바운드의 크기
	D3DXVECTOR3						_boundHalfSize;		//바운드의 절반크기
	float							_boundRadius;		//바운드의 외접구 반지름

	//물리매니져는 내친구
	friend class physicManager;
public:
	xMeshStatic();
	~xMeshStatic();

	virtual HRESULT init(string filePath, D3DXMATRIXA16* matCorrection = NULL);
	virtual void release(void);
	virtual void render(transform* trans);

	//카메라 세팅하기
	static void setCamera(camera* camera);

	//베이스 라이팅 설정 ( 베이스 라이팅은 방향성 광원이다 )
	static void setBaseLight(lightDirection* pDirLight);
	//라이팅 셋팅
	static void setLighting(light** pLights, int lightNum);
	static void setLighting(vector<light*>* pLights);

	//technique 설정
	static void setTechniqueName(string name);

private:
	//보정행렬대로 메쉬를 수정한다
	void meshCorrection(D3DXMATRIXA16* matCorrection);
};

