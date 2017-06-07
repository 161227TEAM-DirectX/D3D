#pragma once
#include "dxModule.h"
class dxAccelerationModule : public dxModule
{
private:

public:
	virtual HRESULT init();
	virtual void relese();
	//virtual void InitUpdate(list<tagDxAttribute>::iterator iter);
	//virtual void ActiveUpdate(list<tagDxAttribute>::iterator iter);

	virtual void InitUpdate(vector<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(vector<tagDxAttribute>::iterator iter);

public:
	//¼Óµµ
	void InitRandomAccelerationX(float min, float max) { _radPtc.accelerationX = tagMaxMin(min, max); _radPtc.radAccelOn = true; }
	void InitRandomAccelerationY(float min, float max) { _radPtc.accelerationY = tagMaxMin(min, max); _radPtc.radAccelOn = true; }
	void InitRandomAccelerationZ(float min, float max) { _radPtc.accelerationZ = tagMaxMin(min, max); _radPtc.radAccelOn = true; }

public:
	dxAccelerationModule() {};
	~dxAccelerationModule() {};
};

