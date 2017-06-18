#pragma once

class quadTree;

class terrainSc
{
private:
	quadTree*						_quadTree;			//���� Ʈ��
	LPDIRECT3DVERTEXBUFFER9			_terrainVb;			//���� ��������
	LPDIRECT3DINDEXBUFFER9			_terrainIb;			//���� �ε�������
	LPDIRECT3DVERTEXDECLARATION9	_terrainDecl;		//���� ��������
	LPTERRAINVERTEX					_terrainVertices;	//���� ��������
	LPD3DXEFFECT					_terrainEffect;		//���� Effect
	LPDIRECT3DTEXTURE9				_heightMap;			//���� ���̸� �ؽ���
	LPDIRECT3DTEXTURE9				_texTile_0;			//���� 3 �� Ÿ�� �ؽ���
	LPDIRECT3DTEXTURE9				_texSlat;			//���÷��� �ؽ���

	LPDIRECT3DTEXTURE9 _texDiffuse;
	LPDIRECT3DTEXTURE9 _texDetail;

	float _cellScale;				//�� ����
	float _heightScale;				//���� ������(�ȼ��÷��� 255�϶� ����)
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

	bool _isVtxRender;				//�������� ����

	char* heightMAPText;

public:
	terrainSc() :_isVtxRender(false), _texDiffuse(NULL), _texDetail(NULL) {}
	~terrainSc() {}

	//����2 �ʱ�ȭ
	HRESULT init(
		char* heightMapName,		//���̸� �̸�
		char* tile_0,				// Ÿ�� �̹��� 3
		char * tileSplat,
		float cellSize,				// �ϳ��� ��ũ��
		float heightScale,			// ���� ������
		int smoothLevel,			// ������ ó�� Ƚ��
		int tileNum);				// Ÿ�ϸ� ����

									//����1 �ʱ�ȭ
	HRESULT initMap(
		int heightNumber,		//���̸� �̸�
		int sizeX,
		int sizeZ,
		float cellSize,
		float heightScale,
		int smoothLevel,
		int tileNum);				//Ÿ�ϸ� ������ ���� �����ϸ��� �׷�����.

	void terrainUpdate(int number);
	void terrainUpdate2(int detailNumber);

	void release(void);
	void render(camera* cam, lightDirection* directionLight);

	//Ray ��Ʈ ��ġ�� ��´�.
	bool isIntersectRay(D3DXVECTOR3* pOut, LPRay ray);

	//�ش� X, Z ��ġ�� ������ ���̸� ��´�.
	float getHeight(float x, float z);

	//�ش� X, Z ��ġ�� ��� ���͸� ��´�.
	bool getSlant(D3DXVECTOR3* pOut, float gravityPower, float x, float z);

	//������ ����
	void setHeight(float x, float z, float delta = 0.1f);

	void render(int diffuseNumber, int detailNumber);
	void setVtxRender(bool isVtxRender=false) { this->_isVtxRender = isVtxRender; }

private:
	//����Ŭ���� ���ο����� ����� �Լ�
	//���� ���� �����
	HRESULT createTerrain(int smooth, int tileNum);
	//���� ������
	void smoothTerrain(int passed);

};

