#pragma once
#include "dijkstra.h"

class quadTree;

class terrain
{
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
	dijkstra*						dijk;				//���ͽ�Ʈ�� Ŭ����

	float _cellScale;				//�� ����
	float _heightScale;				//���� ������(�ȼ��÷��� 255�϶� ����)
	int	  _smoothLevel;				//������ ó�� Ƚ��
	int	  _tileNum;					//Ÿ�ϸ� ����

	int _verNumX;					//���� ������
	int _verNumZ;					//���� ������
	int _totalVerNum;				//��ü ������
	int _cellNumX;					//���� ����
	int _cellNumZ;					//���� ����
	int _totalCellNum;				//��ü ����
	int _totalTriangle;				//��ü �ﰢ����
	float _terrainSizeX;			//���� ���� ������
	float _terrainSizeZ;			//���� ���� ������

									//��Ȯ�� ���� ����� ���� �ʿ��� ������
	float _terrainStartX;			//���� ���� ��ġX
	float _terrainStartZ;			//���� ���� ��ġZ
	float _terrainEndX;				//���� ���� ��ġX
	float _terrainEndZ;				//���� ���� ��ġZ

//=================================================================
//���� ���̰� �ǽð� ������� ������
//=================================================================
public:
	vector<D3DXVECTOR3> _vecPos;		//���̸��� ���� ���̰��� �����Ѵ�.

	LPDIRECT3DTEXTURE9	_brushMap;		//�귯�� ���̸� �ؽ���
	vector<float> _vecBrush;
	int brush_verNumX;					//���� ������
	int brush_verNumZ;					//���� ������
	int brush_totalotalVerNum;			//��ü ������
	int brush_cellNumX;					//���� ����
	int brush_cellNumZ;					//���� ����
	int brush_totalCellNum;				//��ü ����
	float brush_terrainSizeX;			//���� ���� ������
	float brush_terrainSizeZ;			//���� ���� ������
	float _brushScale;					//�귯���� ������
	float _nHeightSign;					//�귯���� ���̰� ���� ��ȣ

public:
	LPD3DXEFFECT _terrainEffect;	//���� Effect
	

public:
	terrain();
	terrain(string terrainEffect);
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

	void render(camera* cam, lightDirection* directionLight);
	void render(camera* cam, lightDirection* directionLight, camera* directionLightCamera);
	void renderShadow(camera* directionLightCam);

	//Ray ��Ʈ ��ġ�� ��´�.
	bool isIntersectRay(D3DXVECTOR3* pOut, LPRay ray);

	//�ش� X, Z ��ġ�� ������ ���̸� ��´�.
	float getHeight(float x, float z);

	//�ش� X, Z ��ġ�� ������ �ε����� ��´�.
	pair<int, int> getIdx(float x, float z);

	//�ش� X, Z ��ġ�� ��� ���͸� ��´�.
	bool getSlant(D3DXVECTOR3* pOut, float gravityPower, float x, float z);

	void setHeightmap(string heightMapName);	//���̸� ����
	void setTile0(string tile_0);			//Ÿ��0 ����
	void setTile1(string tile_1);			//Ÿ��1 ����
	void setTile2(string tile_2);			//Ÿ��2 ����
	void setTile3(string tile_3);			//Ÿ��3 ����
	void setSlat(string tileSplat);			//Ÿ�� �̹��� ��Ʈ�� ����
	void setCellsize(float cellSize);		//�ϳ��� ��ũ�� ����
	void setHeightscale(float heightScale); //���� ������ ����
	void setSmoothlevel(int smoothLevel);	//������ ó�� Ƚ��
	void setTileNum(int tileNum);			//Ÿ�ϸ� ����
	void setBrushmap(string brushMapName);	//�귯�� ����
	void setBrushScale(float scale);		//�귯���� ������ ����
	
	vector<D3DXVECTOR3> getMapPosition()const{ return _vecPos; }
	void setMapPosition(vector<D3DXVECTOR3> vec) { _vecPos = vec; }

	HRESULT changeHeightTerrain();	//�ε带 ���ؼ� ������ ���̰��� �����Ѵ�.
	HRESULT changeHeightTerrain(float cursorX, float cursorZ);	//�귯������ ���ؼ� ������ ���̰��� �����Ѵ�.

	dijkstra&	getDijkstra(void) { return *dijk; }

private:
	//����Ŭ���� ���ο����� ����� �Լ�
	//���� ���� �����
	HRESULT createTerrain(int smooth, int tileNum);
	//���� ������
	void smoothTerrain(int passed);
};

