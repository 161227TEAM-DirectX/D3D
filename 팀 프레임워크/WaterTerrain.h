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
		D3DXVECTOR3 pos;	//��ġ
		DWORD		color;	//����
		float		tu, tv; //�ؽ��� ��ǥ
		enum { FVF_Flags = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
	}WATERVERTEX, *LPWATERVERTEX;

	typedef struct tagWATERTRI
	{
		DWORD dw0;
		DWORD dw1;
		DWORD dw2;
	}WATERTRI, *LPWATERTRI;

private:
	Option_Shader_Water				waterOption;		// �� �ɼ�
	LPDIRECT3DTEXTURE9              temp;               //���ʹ��� ����
	vector<LPDIRECT3DTEXTURE9>		m_pWaterBump;		// ��
	LPDIRECT3DCUBETEXTURE9			m_pReflectionMap;	// �ϴ��� �ݻ� ��
	LPD3DXEFFECT					m_Effect_Water;
	float							m_timer;
	camera							_mainCamera;

private:
	LPDIRECT3DVERTEXBUFFER9			_terrainVb;			//���� ��������
	LPDIRECT3DINDEXBUFFER9			_terrainIb;			//���� �ε�������
	LPWATERVERTEX					_terrainVertices;	//���� ��������

	float _cellScale;				//�� ����
	float _heightScale;				//���� ������(�ȼ��÷��� 255�϶� ����)
	float _terrainSizeX;			//���� ���� ������
	float _terrainSizeZ;			//���� ���� ������

	int _verNumX;					//���� ������
	int _verNumZ;					//���� ������
	int _totalVerNum;				//��ü ������
	int _cellNumX;					//���� ����
	int _cellNumZ;					//���� ����
	int _totalCellNum;				//��ü ����
	int _totalTriangle;				//��ü �ﰢ����

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

