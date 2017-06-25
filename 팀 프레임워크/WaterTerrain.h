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
		enum { FVF_Flags = D3DFVF_XYZ | D3DFVF_DIFFUSE };
	}WATERVERTEX, *LPWATERVERTEX;

	typedef struct tagWATERTRI
	{
		DWORD dw0;
		DWORD dw1;
		DWORD dw2;
	}WATERTRI, *LPWATERTRI;

private:
	Option_Shader_Water				waterOption;		// �� �ɼ�
	LPDIRECT3DTEXTURE9          	m_pWaterBump;		// ��
	vector<LPDIRECT3DCUBETEXTURE9>	m_pReflectionMap;	// �ϴ��� �ݻ� ��
	LPDIRECT3DCUBETEXTURE9          temp;               //���ʹ��� ����
	LPD3DXEFFECT					m_Effect_Water;
	float							m_timer;

private:
	camera* _mainCamera;

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

	void linkCamera(camera& temp) { this->_mainCamera = &temp; }

};

