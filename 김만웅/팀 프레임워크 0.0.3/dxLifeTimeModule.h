#pragma once
#include "dxModule.h"
class dxLifeTimeModule :public dxModule
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
	void InitRandomLiftTime(float min, float max) { _radPtc.lifeTime = tagMaxMin(min, max); _radPtc.radLifeOn = true; }

public:
	dxLifeTimeModule() {};
	~dxLifeTimeModule() {};
};

