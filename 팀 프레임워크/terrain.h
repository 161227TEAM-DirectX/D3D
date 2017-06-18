#pragma once
#include "dijkstra.h"

class quadTree;

class terrain
{
private:
	quadTree*						_quadTree;			//쿼드 트리
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
	dijkstra*						dijk;				//다익스트라 클래스

	float _cellScale;				//셀 간격
	float _heightScale;				//높이 스케일(픽셀컬러가 255일때 높이)
	int	  _smoothLevel;				//스무싱 처리 횟수
	int	  _tileNum;					//타일링 갯수

	int _verNumX;					//가로 정점수
	int _verNumZ;					//깊이 정점수
	int _totalVerNum;				//전체 정점수
	int _cellNumX;					//가로 셀수
	int _cellNumZ;					//깊이 셀수
	int _totalCellNum;				//전체 셀수
	int _totalTriangle;				//전체 삼각형수
	float _terrainSizeX;			//지형 가로 사이즈
	float _terrainSizeZ;			//지형 세로 사이즈

									//정확한 높이 계산을 위해 필요한 변수들
	float _terrainStartX;			//지형 시작 위치X
	float _terrainStartZ;			//지형 시작 위치Z
	float _terrainEndX;				//지형 종료 위치X
	float _terrainEndZ;				//지형 종료 위치Z

//=================================================================
//지형 높이값 실시간 변경관련 변수들
//=================================================================
public:
	vector<D3DXVECTOR3> _vecPos;		//높이맵의 현재 높이값을 저장한다.

	LPDIRECT3DTEXTURE9	_brushMap;		//브러쉬 높이맵 텍스쳐
	vector<float> _vecBrush;
	int brush_verNumX;					//가로 정점수
	int brush_verNumZ;					//깊이 정점수
	int brush_totalotalVerNum;			//전체 정점수
	int brush_cellNumX;					//가로 셀수
	int brush_cellNumZ;					//깊이 셀수
	int brush_totalCellNum;				//전체 셀수
	float brush_terrainSizeX;			//지형 가로 사이즈
	float brush_terrainSizeZ;			//지형 세로 사이즈
	float _brushScale;					//브러쉬맵 스케일
	float _nHeightSign;					//브러쉬맵 높이값 조절 부호

public:
	LPD3DXEFFECT _terrainEffect;	//지형 Effect
	

public:
	terrain();
	terrain(string terrainEffect);
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

	void render(camera* cam, lightDirection* directionLight);
	void render(camera* cam, lightDirection* directionLight, camera* directionLightCamera);
	void renderShadow(camera* directionLightCam);

	//Ray 히트 위치를 얻는다.
	bool isIntersectRay(D3DXVECTOR3* pOut, LPRay ray);

	//해당 X, Z 위치의 지형의 높이를 얻는다.
	float getHeight(float x, float z);

	//해당 X, Z 위치의 지형의 인덱스를 얻는다.
	pair<int, int> getIdx(float x, float z);

	//해당 X, Z 위치의 경사 벡터를 얻는다.
	bool getSlant(D3DXVECTOR3* pOut, float gravityPower, float x, float z);

	void setHeightmap(string heightMapName);	//높이맵 셋팅
	void setTile0(string tile_0);			//타일0 셋팅
	void setTile1(string tile_1);			//타일1 셋팅
	void setTile2(string tile_2);			//타일2 셋팅
	void setTile3(string tile_3);			//타일3 셋팅
	void setSlat(string tileSplat);			//타일 이미지 컨트롤 셋팅
	void setCellsize(float cellSize);		//하나의 셀크기 셋팅
	void setHeightscale(float heightScale); //높이 스케일 셋팅
	void setSmoothlevel(int smoothLevel);	//스무싱 처리 횟수
	void setTileNum(int tileNum);			//타일링 갯수
	void setBrushmap(string brushMapName);	//브러쉬 셋팅
	void setBrushScale(float scale);		//브러쉬맵 스케일 셋팅
	
	vector<D3DXVECTOR3> getMapPosition()const{ return _vecPos; }
	void setMapPosition(vector<D3DXVECTOR3> vec) { _vecPos = vec; }

	HRESULT changeHeightTerrain();	//로드를 통해서 지형의 높이값을 변경한다.
	HRESULT changeHeightTerrain(float cursorX, float cursorZ);	//브러쉬맵을 통해서 지형의 높이값을 변경한다.

	dijkstra&	getDijkstra(void) { return *dijk; }

private:
	//지형클래스 내부에서만 사용할 함수
	//지형 정점 만들기
	HRESULT createTerrain(int smooth, int tileNum);
	//지형 스무싱
	void smoothTerrain(int passed);
};

