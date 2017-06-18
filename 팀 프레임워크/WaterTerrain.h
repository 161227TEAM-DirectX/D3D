#pragma once
#include "iGameNode.h"

class WaterTerrain : public iGameNode
{

private:
	struct Option_Shader_Water
	{
		bool							AlphaLayer;
		bool							_using;

		D3DXVECTOR2						textureScale;
		float							waveFreq;
		float							waveAmp;

		float							BumpScale;
		D3DXVECTOR2						bumpSpeed;
		D3DXVECTOR4						deepColor;
		D3DXVECTOR4						shallowColor;
		float							waterAmount;

		D3DXVECTOR4						reflectionColor;
		float							reflectionAmount;
		float							reflectionBlur;

		float							fresnelPower;
		float							fresnelBias;
		float							hdrMultiplier;
	};

public:
	typedef struct tagWATERVERTEX
	{
		D3DXVECTOR3 pos;	//위치
		DWORD		color;	//색깔
		float		tu, tv; //텍스쳐 좌표
		enum { FVF_Flags = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
	}WATERVERTEX, *LPWATERVERTEX;

	typedef struct tagWATERTRI
	{
		DWORD dw0;
		DWORD dw1;
		DWORD dw2;
	}WATERTRI, *LPWATERTRI;

private:
	Option_Shader_Water				waterOption;		// 물 옵션
	LPDIRECT3DTEXTURE9              temp;               //벡터담을 변수
	vector<LPDIRECT3DTEXTURE9>		m_pWaterBump;		// 물
	LPDIRECT3DCUBETEXTURE9			m_pReflectionMap;	// 하늘의 반사 맵
	LPD3DXEFFECT					m_Effect_Water;
	float							m_timer;
	camera							_mainCamera;

private:
	LPDIRECT3DVERTEXBUFFER9			_terrainVb;			//지형 정점버퍼
	LPDIRECT3DINDEXBUFFER9			_terrainIb;			//지형 인덱스버퍼
	LPWATERVERTEX					_terrainVertices;	//지형 정점정보

	float _cellScale;				//셀 간격
	float _heightScale;				//높이 스케일(픽셀컬러가 255일때 높이)
	float _terrainSizeX;			//지형 가로 사이즈
	float _terrainSizeZ;			//지형 세로 사이즈

	int _verNumX;					//가로 정점수
	int _verNumZ;					//깊이 정점수
	int _totalVerNum;				//전체 정점수
	int _cellNumX;					//가로 셀수
	int _cellNumZ;					//깊이 셀수
	int _totalCellNum;				//전체 셀수
	int _totalTriangle;				//전체 삼각형수

	float _flowAngle;

public:
	WaterTerrain();
	~WaterTerrain();

	HRESULT init();
	HRESULT init(float cellSize, int tileNum);
	void release();
	void update(){}
	void update(int number);
	void render(){}
	void render(int number);
};

