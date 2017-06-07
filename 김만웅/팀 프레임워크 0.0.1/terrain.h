#pragma once

class quadTree;

class terrain
{
public:
	//Terrain ���� ����ü
	typedef struct tagTERRAINVERTEX 
	{
		D3DXVECTOR3 pos;			//��ġ
		D3DXVECTOR3 normal;			//�븻
		D3DXVECTOR3 binormal;		//���̳븻
		D3DXVECTOR3 tangent;		//ź��Ʈ
		D3DXVECTOR2 baseUV;			//0~1 UV
		D3DXVECTOR2 tileUV;			//Ÿ�� UV 
	}TERRAINVERTEX, *LPTERRAINVERTEX;

	//Terrain �ε��� ����ü ( ��� ����ü �ϳ��� �ﰢ�� �ϳ��� ����Ѵ� )
	typedef struct tagTERRAINTRI 
	{
		DWORD dw0;
		DWORD dw1;
		DWORD dw2;
	}TERRAINTRI, *LPTERRAINTRI;

private:
	quadTree*						_quadTree;			//���� Ʈ��
	LPDIRECT3DVERTEXBUFFER9			_terrainVb;			//���� ��������
	LPDIRECT3DINDEXBUFFER9			_terrainIb;			//���� �ε�������
	LPDIRECT3DVERTEXDECLARATION9	_terrainDecl;		//���� ��������
	LPTERRAINVERTEX					_terrainVertices;	//���� ��������
	LPDIRECT3DTEXTURE9				_heightMap;			//���� ���̸� �ؽ���
	LPDIRECT3DTEXTURE9				_texTile_0;			//���� 0 �� Ÿ�� �ؽ���
	LPDIRECT3DTEXTURE9				_texTile_1;			//���� 1 �� Ÿ�� �ؽ���
	LPDIRECT3DTEXTURE9				_texTile_2;			//���� 2 �� Ÿ�� �ؽ���
	LPDIRECT3DTEXTURE9				_texTile_3;			//���� 3 �� Ÿ�� �ؽ���
	LPDIRECT3DTEXTURE9				_texSlat;			//���÷��� �ؽ���

	float _cellScale;				//�� ����
	float _heightScale;				//���� ������(�ȼ��÷��� 255�϶� ����)
	int _verNumX;					//���� ������
	int _verNumZ;					//���� ������
	int _totalVerNum;				//��ü ������
	int _cellNumX;					//���� ����
	int _cellNumZ;					//���� ����
	int _totalCellNum;				//��ü ����
	int _totalTriangle;				//��ü �ﰢ����
	float _terrainSizeX;				//���� ���� ������
	float _terrainSizeZ;				//���� ���� ������


	//��Ȯ�� ���� ����� ���� �ʿ��� ������
	float _terrainStartX;			//���� ���� ��ġX
	float _terrainStartZ;			//���� ���� ��ġZ
	float _terrainEndX;				//���� ���� ��ġX
	float _terrainEndZ;				//���� ���� ��ġZ

public:
	LPD3DXEFFECT _terrainEffect;	//���� Effect

public:
	terrain() {}
	~terrain() {}
	//���� �ʱ�ȭ
	HRESULT init(
		char* heightMapName,		//���̸� �̸�
		char* tile_0,				// Ÿ�� �̹��� 0
		char* tile_1,				// Ÿ�� �̹��� 1
		char* tile_2,				// Ÿ�� �̹��� 2
		char* tile_3,				// Ÿ�� �̹��� 3
		char* tileSplat,			// Ÿ�� �̹��� ��Ʈ�� (RGB Black)
		float cellSize,				// �ϳ��� ��ũ��
		float heightScale,			// ���� ������
		int smoothLevel,			// ������ ó�� Ƚ��
		int tileNum);				// Ÿ�ϸ� ����

	void release(void);
	void render(camera* cam, lightDirection* directionLight);
	void render(camera* cam, lightDirection* directionLight, camera* directionLightCamera);
	void renderShadow(camera* directionLightCam);

	//Ray ��Ʈ ��ġ�� ��´�.
	bool isIntersectRay(D3DXVECTOR3* pOut, LPRay ray);

	//�ش� X, Z ��ġ�� ������ ���̸� ��´�.
	float getHeight(float x, float z);

	//�ش� X, Z ��ġ�� ��� ���͸� ��´�.
	bool getSlant(D3DXVECTOR3* pOut, float gravityPower, float x, float z);

private:
	//����Ŭ���� ���ο����� ����� �Լ�
	//���� ���� �����
	HRESULT createTerrain(int smooth, int tileNum);
	//���� ������
	void smoothTerrain(int passed);

};

