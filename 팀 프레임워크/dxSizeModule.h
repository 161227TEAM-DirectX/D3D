#pragma once
#include "dxModule.h"
class dxSizeModule : public dxModule
{
private:
	vector<tagDxGraph*> _grpSize;
	bool _grpSizeOn;

public:
	virtual HRESULT init();
	virtual void relese();
	virtual void InitUpdate(vector<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(vector<tagDxAttribute>::iterator iter);
public:
	//사이즈 세팅
	void InitRandomSize(float min, float max) { _radPtc.sizeInit = tagMaxMin(min, max); _radPtc.radSizeInitOn = true; }
	void InitRandomSizeEnd(float min, float max) { _radPtc.sizeEnd = tagMaxMin(min, max); _radPtc.radSizeEndOn = true; }

	//사이즈 그래프 세팅
	void addSizeGraph(float point, float min, float max) { GraphCheck(_grpSize, point, min, max); _grpSizeOn = true; }

	//가로세로
	void InitConstHV(float horizontal, float vertical) { _radPtc.horizontal = horizontal; _radPtc.vertical = vertical; }

	//면 상에서 중심 위치를 세팅
	void InitCenterPointHV(float pointH, float pointV) { _radPtc.centerPointHV.x = pointH, _radPtc.centerPointHV.y = pointV; _radPtc.centerPointHV_On = true; }

public:
	dxSizeModule() {};
	~dxSizeModule() {};
};

