#pragma once
#include "dxModule.h"
class dxCircleModule :	public dxModule
{
private:
	vector<tagDxGraph*> _grpRadius;
	bool _grpRadiusOn;

	D3DXVECTOR3 _preCircle;

public:
	virtual HRESULT init();
	virtual void relese();
	//virtual void InitUpdate(list<tagDxAttribute>::iterator iter);
	//virtual void ActiveUpdate(list<tagDxAttribute>::iterator iter);

	virtual void InitUpdate(vector<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(vector<tagDxAttribute>::iterator iter);

public:
	//반지름 세팅
	void InitRandomRadiusX(float min, float max) { _radPtc.radiusInitX = tagMaxMin(min, max); _radPtc.circleX_On = true; }
	void InitRandomRadiusY(float min, float max) { _radPtc.radiusInitY = tagMaxMin(min, max); _radPtc.circleY_On = true; }
	void InitRandomRadiusZ(float min, float max) { _radPtc.radiusInitZ = tagMaxMin(min, max); _radPtc.circleZ_On = true; }

	//반지름 마지막
	void InitRandomRadiusEndX(float min, float max) { _radPtc.radiusEndX = tagMaxMin(min, max); _radPtc.radiusEndX_On = true; }
	void InitRandomRadiusEndY(float min, float max) { _radPtc.radiusEndY = tagMaxMin(min, max); _radPtc.radiusEndY_On = true; }
	void InitRandomRadiusEndZ(float min, float max) { _radPtc.radiusEndZ = tagMaxMin(min, max); _radPtc.radiusEndZ_On = true; }

	//반지름 그래프
	void addRadiusGraph(float point, float min, float max) { GraphCheck(_grpRadius, point, min, max); _grpRadiusOn = true; }

	//각도 스피드
	void InitCircleAngleSpeedX(float min, float max) { _radPtc.circleAngleSpeedX = tagMaxMin(min, max); _radPtc.circleX_On = true; }
	void InitCircleAngleSpeedY(float min, float max) { _radPtc.circleAngleSpeedY = tagMaxMin(min, max); _radPtc.circleY_On = true; }
	void InitCircleAngleSpeedZ(float min, float max) { _radPtc.circleAngleSpeedZ = tagMaxMin(min, max); _radPtc.circleZ_On = true; }

	//시작 각도
	void InitCircleStartAngleX(float min, float max) { _radPtc.circleStartAngleX = tagMaxMin(min, max); _radPtc.circleX_On = true; }
	void InitCircleStartAngleY(float min, float max) { _radPtc.circleStartAngleY = tagMaxMin(min, max); _radPtc.circleY_On = true; }
	void InitCircleStartAngleZ(float min, float max) { _radPtc.circleStartAngleZ = tagMaxMin(min, max); _radPtc.circleZ_On = true; }

public:
	dxCircleModule() {};
	~dxCircleModule() {};
};

