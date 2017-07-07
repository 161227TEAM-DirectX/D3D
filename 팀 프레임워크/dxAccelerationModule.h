#pragma once
#include "dxModule.h"
class dxAccelerationModule : public dxModule
{
private:
	vector<tagDxGraph*> _grpAccelX;
	vector<tagDxGraph*> _grpAccelY;
	vector<tagDxGraph*> _grpAccelZ;
	bool _grpAccelX_On;
	bool _grpAccelY_On;
	bool _grpAccelZ_On;

public:
	virtual HRESULT init();
	virtual void relese();
	//virtual void InitUpdate(list<tagDxAttribute>::iterator iter);
	//virtual void ActiveUpdate(list<tagDxAttribute>::iterator iter);

	virtual void InitUpdate(vector<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(vector<tagDxAttribute>::iterator iter);

public:
	//가속도
	void InitRandomAccelerationX(float min, float max) { _radPtc.accelerationX = tagMaxMin(min, max); _radPtc.radAccelOn = true; }
	void InitRandomAccelerationY(float min, float max) { _radPtc.accelerationY = tagMaxMin(min, max); _radPtc.radAccelOn = true; }
	void InitRandomAccelerationZ(float min, float max) { _radPtc.accelerationZ = tagMaxMin(min, max); _radPtc.radAccelOn = true; }

	//가속도 그래프
	void addAccelGraphX(float point, float min, float max) { GraphCheck(_grpAccelX, point, min, max); _grpAccelX_On = true; }
	void addAccelGraphY(float point, float min, float max) { GraphCheck(_grpAccelY, point, min, max); _grpAccelY_On = true; }
	void addAccelGraphZ(float point, float min, float max) { GraphCheck(_grpAccelZ, point, min, max); _grpAccelZ_On = true; }


public:
	dxAccelerationModule() {};
	~dxAccelerationModule() {};
};

