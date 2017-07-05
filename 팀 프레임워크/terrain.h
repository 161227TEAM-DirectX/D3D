#pragma once
#include "dijkstra.h"

class quadTree;

class terrain
{
private:
	LPDIRECT3DVERTEXBUFFER9			_terrainVb;			//지형 정점버퍼
	LPDIRECT3DINDEXBUFFER9			_terrainIb;			//지형 인덱스버퍼
	LPDIRECT3DVERTEXDECLARATION9	_terrainDecl;		//정점 정보선언
	LPTERRAINVERTEX					_terrainVertices;	//지형 정점정보

	LPDIRECT3DTEXTURE9				_heightMap;			//지형 높이맵 텍스쳐
	LPDIRECT3DTEXTURE9				_texTile_0;			//지형 0 층 타일 텍스쳐
	LPDIRECT3DTEXTURE9				_texTile_1;			//지형 1 층 타일 텍스쳐
	LPDIRECT3DTEXTURE9				_texTile_2;			//지형 2 층 타일 텍스쳐
	LPDIRECT3DTEXTURE9				_texTile_3;			//지형 3 층 타일 텍스쳐
	LPDIRECT3DTEXTURE9				_texSlat;			//스플렛팅 텍스쳐

	SYNTHESIZE(quadTree*, _quadTree, QuadTree);			//쿼드 트리
	SYNTHESIZE(bool, _isQuad, IsQuad);					//쿼드 실행 여부

	SYNTHESIZE(float, _cellScale, CellScale);			//셀 간격
	SYNTHESIZE(float, _heightScale, HeightScale);		//높이 스케일(픽셀컬러가 255일때 높이)
	SYNTHESIZE(int, _smoothLevel, SmoothLevel);			//스무싱 처리 횟수
	SYNTHESIZE(int, _tileNum, TileNum);					//타일링 갯수
	SYNTHESIZE(int, _verNumX, VerNumX);					//가로 정점수(실제 그림 사이즈 보다 1개 더 많다.이해가 안되면 그림을 그려볼 것.)
	SYNTHESIZE(int, _verNumZ, VerNumZ);					//세로 정점수(실제 그림 사이즈 보다 1개 더 많다.이해가 안되면 그림을 그려볼 것.)
	SYNTHESIZE(int, _totalVerNum, TotalVerNum);			//전체 정점수(가로 정점수 * 세로 정점수)
	SYNTHESIZE(int, _cellNumX, CellNumX);				//가로 셀수(실제 그림 사이즈)
	SYNTHESIZE(int, _cellNumZ, CellNumZ);				//세로 셀수(실제 그림 사이즈)
	SYNTHESIZE(int, _totalCellNum, TotalCellNum);		//전체 셀수
	SYNTHESIZE(int, _totalTriangle, TotalTriangle);		//전체 삼각형수		
	SYNTHESIZE(float, _terrainSizeX, TerrainSizeX);		//지형 가로 사이즈(128,256,같은)
	SYNTHESIZE(float, _terrainSizeZ, TerrainSizeZ);		//지형 세로 사이즈(128,256,같은)
	SYNTHESIZE(float, _terrainStartX, TerrainStartX);	//지형 시작 위치X
	SYNTHESIZE(float, _terrainStartZ, TerrainStartZ);	//지형 시작 위치Z
	SYNTHESIZE(float, _terrainEndX, TerrainEndX);		//지형 종료 위치X
	SYNTHESIZE(float, _terrainEndZ, TerrainEndZ);		//지형 종료 위치Z
	SYNTHESIZE(bool, _isVertexDraw, IsVertexDraw);		//버텍스 지형을 그릴건지
	SYNTHESIZE(int, _nHtChangeRange, HtChangeRange);	//높이값을 바꿀 범위(영역)
	SYNTHESIZE(float, _fHtChangeValue, HtChangeValue);	//높이값을 바꿀 값(얼마만큼 올리고 내릴건지)
	SYNTHESIZE(int, _nHtChangeSign, HtChangeSign);		//높이값을 증가시킬지 감소시킬지 부호
	SYNTHESIZE(bool, _isSmoothing, IsSmoothing);		//스무싱을 할건지


//=================================================================
// 지형 Effect
//=================================================================
public:
	LPD3DXEFFECT _terrainEffect;	//지형 Effect


public:
	terrain();
	~terrain();

	//지형 초기화
	HRESULT init(
		char* heightMapName,		//높이맵 이름
		char* tile_0,				// 타일 이미지 0
		char* tile_1,				// 타일 이미지 1
		char* tile_2,				// 타일 이미지 2
		char* tile_3,				// 타일 이미지 3
		char* tileSplat,			// 타일 이미지 컨트롤 (RGB Black)
		float cellSize,				// 하나의 셀크기
		float heightScale,			// 높이 스케일
		int smoothLevel,			// 스무싱 처리 횟수
		int tileNum);				// 타일링 갯수

									//지형 관련 정보셋팅한 것들을 갱신한다.
	void setting();

	//지형 높이값을 바꾼다.
	void changeHeight(int terrainX, int terrainZ);

	//지형을 그린다.
	void render(camera* cam, lightDirection* directionLight);
	void render(camera* cam, lightDirection* directionLight, camera* directionLightCamera);
	void renderShadow(camera* directionLightCam);

	//Ray 히트 위치를 얻는다.
	bool isIntersectRay(D3DXVECTOR3* pOut, LPRay ray);

	//해당 X, Z 위치의 지형의 높이를 얻는다.
	float getHeight(float x, float z);

	//해당 X, Z 위치의 지형의 인덱스를 얻는다.
	D3DXVECTOR2 getIdx(float x, float z);

	//해당 X, Z 위치의 경사 벡터를 얻는다.
	bool getSlant(D3DXVECTOR3* pOut, float gravityPower, float x, float z);

	//지형 정점 만들기
	HRESULT createTerrain(int tileNum);
	HRESULT changeTerrainHt(int terrainX, int terrainZ);

	//지형 스무싱
	void smoothTerrain();
	void smoothChangeTerrainHt(int terrainX, int terrainZ);

	//선택한 곳의 스플랫맵에서의 색상을 얻어온다.
	D3DXVECTOR3 selectSplatColor(string splatName, int x, int z);

	void setHeightmap(string heightMapName);	//높이맵 셋팅
	void setHeightmap(string heightMapName, bool isOver);	//높이맵 셋팅

	void setTile0(string tile_0);				//타일0 셋팅
	void setTile1(string tile_1);				//타일1 셋팅
	void setTile2(string tile_2);				//타일2 셋팅
	void setTile3(string tile_3);				//타일3 셋팅

	void setTile0(string tile_0, bool isOver);				//타일0 셋팅
	void setTile1(string tile_1, bool isOver);				//타일1 셋팅
	void setTile2(string tile_2, bool isOver);				//타일2 셋팅
	void setTile3(string tile_3, bool isOver);				//타일3 셋팅

	void setSplat(string tileSplat);			//타일 이미지 컨트롤 셋팅
	void setSplat(string tileSplat, bool isOver);			//타일 이미지 컨트롤 셋팅
	void setSplat(LPDIRECT3DTEXTURE9 texSlat);	//타일 이미지 컨트롤 셋팅

	void setCellsize(float cellSize);			//하나의 셀크기 셋팅
	void setHeightscale(float heightScale);		//높이 스케일 셋팅
	void setSmoothlevel(int smoothLevel);		//스무싱 처리 횟수
	void setTileNum(int tileNum);				//타일링 갯수



//=========================================================================
// 다익스트라
//=========================================================================
private:
	dijkstra* dijk;	//쿼드 트리
public:
	dijkstra&	getDijkstra(void) { return *dijk; }



//=========================================================================
//지형 높이값 실시간 변경 브러쉬 방법 -> 프레임 드랍과 더불어 온갖 버그...
//=========================================================================
public:
	vector<D3DXVECTOR3> _vecPos;		//높이맵의 현재 높이값을 저장한다.
	LPDIRECT3DTEXTURE9	_brushMap;		//브러쉬 높이맵 텍스쳐
	vector<float> _vecBrush;
	int brush_verNumX = 0;				//가로 정점수
	int brush_verNumZ = 0;				//깊이 정점수
	int brush_totalotalVerNum = 0;		//전체 정점수
	int brush_cellNumX = 0;				//가로 셀수
	int brush_cellNumZ = 0;				//깊이 셀수
	int brush_totalCellNum = 0;			//전체 셀수
	float brush_terrainSizeX = 0;		//지형 가로 사이즈
	float brush_terrainSizeZ = 0;		//지형 세로 사이즈
	float _brushScale = 10.f;			//브러쉬맵 스케일
	float _nHeightSign = 1.f;			//브러쉬맵 높이값 조절 부호

										//로드를 통해서 지형의 높이값을 변경한다.
	HRESULT changeHeightTerrain();

	//브러쉬맵을 통해서 지형의 높이값을 변경한다.
	HRESULT changeHeightTerrain(float cursorX, float cursorZ);

	void setBrushmap(string brushMapName);		//브러쉬 셋팅
	void setBrushScale(float scale);			//브러쉬맵 스케일 셋팅

	vector<D3DXVECTOR3> getMapPosition()const { return _vecPos; }
	void setMapPosition(vector<D3DXVECTOR3> vec) { _vecPos = vec; }
};

