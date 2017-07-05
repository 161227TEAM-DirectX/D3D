#pragma once
#include "dijkstra.h"

class quadTree;

class terrain
{
private:
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

	SYNTHESIZE(quadTree*, _quadTree, QuadTree);			//���� Ʈ��
	SYNTHESIZE(bool, _isQuad, IsQuad);					//���� ���� ����

	SYNTHESIZE(float, _cellScale, CellScale);			//�� ����
	SYNTHESIZE(float, _heightScale, HeightScale);		//���� ������(�ȼ��÷��� 255�϶� ����)
	SYNTHESIZE(int, _smoothLevel, SmoothLevel);			//������ ó�� Ƚ��
	SYNTHESIZE(int, _tileNum, TileNum);					//Ÿ�ϸ� ����
	SYNTHESIZE(int, _verNumX, VerNumX);					//���� ������(���� �׸� ������ ���� 1�� �� ����.���ذ� �ȵǸ� �׸��� �׷��� ��.)
	SYNTHESIZE(int, _verNumZ, VerNumZ);					//���� ������(���� �׸� ������ ���� 1�� �� ����.���ذ� �ȵǸ� �׸��� �׷��� ��.)
	SYNTHESIZE(int, _totalVerNum, TotalVerNum);			//��ü ������(���� ������ * ���� ������)
	SYNTHESIZE(int, _cellNumX, CellNumX);				//���� ����(���� �׸� ������)
	SYNTHESIZE(int, _cellNumZ, CellNumZ);				//���� ����(���� �׸� ������)
	SYNTHESIZE(int, _totalCellNum, TotalCellNum);		//��ü ����
	SYNTHESIZE(int, _totalTriangle, TotalTriangle);		//��ü �ﰢ����		
	SYNTHESIZE(float, _terrainSizeX, TerrainSizeX);		//���� ���� ������(128,256,����)
	SYNTHESIZE(float, _terrainSizeZ, TerrainSizeZ);		//���� ���� ������(128,256,����)
	SYNTHESIZE(float, _terrainStartX, TerrainStartX);	//���� ���� ��ġX
	SYNTHESIZE(float, _terrainStartZ, TerrainStartZ);	//���� ���� ��ġZ
	SYNTHESIZE(float, _terrainEndX, TerrainEndX);		//���� ���� ��ġX
	SYNTHESIZE(float, _terrainEndZ, TerrainEndZ);		//���� ���� ��ġZ
	SYNTHESIZE(bool, _isVertexDraw, IsVertexDraw);		//���ؽ� ������ �׸�����
	SYNTHESIZE(int, _nHtChangeRange, HtChangeRange);	//���̰��� �ٲ� ����(����)
	SYNTHESIZE(float, _fHtChangeValue, HtChangeValue);	//���̰��� �ٲ� ��(�󸶸�ŭ �ø��� ��������)
	SYNTHESIZE(int, _nHtChangeSign, HtChangeSign);		//���̰��� ������ų�� ���ҽ�ų�� ��ȣ
	SYNTHESIZE(bool, _isSmoothing, IsSmoothing);		//�������� �Ұ���


//=================================================================
// ���� Effect
//=================================================================
public:
	LPD3DXEFFECT _terrainEffect;	//���� Effect


public:
	terrain();
	~terrain();

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

									//���� ���� ���������� �͵��� �����Ѵ�.
	void setting();

	//���� ���̰��� �ٲ۴�.
	void changeHeight(int terrainX, int terrainZ);

	//������ �׸���.
	void render(camera* cam, lightDirection* directionLight);
	void render(camera* cam, lightDirection* directionLight, camera* directionLightCamera);
	void renderShadow(camera* directionLightCam);

	//Ray ��Ʈ ��ġ�� ��´�.
	bool isIntersectRay(D3DXVECTOR3* pOut, LPRay ray);

	//�ش� X, Z ��ġ�� ������ ���̸� ��´�.
	float getHeight(float x, float z);

	//�ش� X, Z ��ġ�� ������ �ε����� ��´�.
	D3DXVECTOR2 getIdx(float x, float z);

	//�ش� X, Z ��ġ�� ��� ���͸� ��´�.
	bool getSlant(D3DXVECTOR3* pOut, float gravityPower, float x, float z);

	//���� ���� �����
	HRESULT createTerrain(int tileNum);
	HRESULT changeTerrainHt(int terrainX, int terrainZ);

	//���� ������
	void smoothTerrain();
	void smoothChangeTerrainHt(int terrainX, int terrainZ);

	//������ ���� ���÷��ʿ����� ������ ���´�.
	D3DXVECTOR3 selectSplatColor(string splatName, int x, int z);

	void setHeightmap(string heightMapName);	//���̸� ����
	void setHeightmap(string heightMapName, bool isOver);	//���̸� ����

	void setTile0(string tile_0);				//Ÿ��0 ����
	void setTile1(string tile_1);				//Ÿ��1 ����
	void setTile2(string tile_2);				//Ÿ��2 ����
	void setTile3(string tile_3);				//Ÿ��3 ����

	void setTile0(string tile_0, bool isOver);				//Ÿ��0 ����
	void setTile1(string tile_1, bool isOver);				//Ÿ��1 ����
	void setTile2(string tile_2, bool isOver);				//Ÿ��2 ����
	void setTile3(string tile_3, bool isOver);				//Ÿ��3 ����

	void setSplat(string tileSplat);			//Ÿ�� �̹��� ��Ʈ�� ����
	void setSplat(string tileSplat, bool isOver);			//Ÿ�� �̹��� ��Ʈ�� ����
	void setSplat(LPDIRECT3DTEXTURE9 texSlat);	//Ÿ�� �̹��� ��Ʈ�� ����

	void setCellsize(float cellSize);			//�ϳ��� ��ũ�� ����
	void setHeightscale(float heightScale);		//���� ������ ����
	void setSmoothlevel(int smoothLevel);		//������ ó�� Ƚ��
	void setTileNum(int tileNum);				//Ÿ�ϸ� ����



//=========================================================================
// ���ͽ�Ʈ��
//=========================================================================
private:
	dijkstra* dijk;	//���� Ʈ��
public:
	dijkstra&	getDijkstra(void) { return *dijk; }



//=========================================================================
//���� ���̰� �ǽð� ���� �귯�� ��� -> ������ ����� ���Ҿ� �°� ����...
//=========================================================================
public:
	vector<D3DXVECTOR3> _vecPos;		//���̸��� ���� ���̰��� �����Ѵ�.
	LPDIRECT3DTEXTURE9	_brushMap;		//�귯�� ���̸� �ؽ���
	vector<float> _vecBrush;
	int brush_verNumX = 0;				//���� ������
	int brush_verNumZ = 0;				//���� ������
	int brush_totalotalVerNum = 0;		//��ü ������
	int brush_cellNumX = 0;				//���� ����
	int brush_cellNumZ = 0;				//���� ����
	int brush_totalCellNum = 0;			//��ü ����
	float brush_terrainSizeX = 0;		//���� ���� ������
	float brush_terrainSizeZ = 0;		//���� ���� ������
	float _brushScale = 10.f;			//�귯���� ������
	float _nHeightSign = 1.f;			//�귯���� ���̰� ���� ��ȣ

										//�ε带 ���ؼ� ������ ���̰��� �����Ѵ�.
	HRESULT changeHeightTerrain();

	//�귯������ ���ؼ� ������ ���̰��� �����Ѵ�.
	HRESULT changeHeightTerrain(float cursorX, float cursorZ);

	void setBrushmap(string brushMapName);		//�귯�� ����
	void setBrushScale(float scale);			//�귯���� ������ ����

	vector<D3DXVECTOR3> getMapPosition()const { return _vecPos; }
	void setMapPosition(vector<D3DXVECTOR3> vec) { _vecPos = vec; }
};

