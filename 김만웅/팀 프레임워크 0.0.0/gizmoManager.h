#pragma once
#include "singletonBase.h"

#define CIRCLEGIZMO_SEGMENTS 36

class gizmoManager : public singletonBase <gizmoManager>
{
private:
	typedef struct tagGizmoVertex
	{
		D3DXVECTOR3 pos;		//정점의 위치
		DWORD		color;		//정점의 컬러
		enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
	}GIZMOVERTEX, *LPGIZMOVERTEX;

private:
	D3DXVECTOR3 _circlePos[CIRCLEGIZMO_SEGMENTS + 1]; //원의 정점 위치

public:
	HRESULT init(void);
	void release(void);

	//선을 그리는 함수
	void Line(D3DXVECTOR3& startPos, D3DXVECTOR3& endPos, DWORD color = 0xff808080);
	//월드 그리는 함수
	void WorldGrid(float cellSize, int cellNum);
	//원을 그리는 함수
	void Circle(D3DXVECTOR3& centerPos, float radius, D3DXVECTOR3& axis = D3DXVECTOR3(0, 0, 1), DWORD color = 0xff808080);
	//와이어 구를 그리는 함수
	void WireSphere(D3DXVECTOR3& centerPos, float radius, DWORD color = 0xff808080);
	//월드 AABB를 그리는 함수
	void AABB(D3DXVECTOR3& minPos, D3DXVECTOR3& maxPos, DWORD color = 0xff808080);


	gizmoManager() {}
	~gizmoManager() {}
};

