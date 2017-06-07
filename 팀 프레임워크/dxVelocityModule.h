#pragma once
#include "dxModule.h"
class dxVelocityModule : public dxModule
{
private:
	vector<tagDxGraph*> _grpVelocityX;
	vector<tagDxGraph*> _grpVelocityY;
	vector<tagDxGraph*> _grpVelocityZ;
	bool _grpVelocityX_On;
	bool _grpVelocityY_On;
	bool _grpVelocityZ_On;

public:
	virtual HRESULT init();
	virtual void relese();
	//virtual void InitUpdate(list<tagDxAttribute>::iterator iter);
	//virtual void ActiveUpdate(list<tagDxAttribute>::iterator iter);

	virtual void InitUpdate(vector<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(vector<tagDxAttribute>::iterator iter);

public:
	//속도 초기화
	void InitRandomVelocityX(float min, float max) { _radPtc.velocityX = tagMaxMin(min, max); _radPtc.radVelOn = true; }
	void InitRandomVelocityY(float min, float max) { _radPtc.velocityY = tagMaxMin(min, max); _radPtc.radVelOn = true; }
	void InitRandomVelocityZ(float min, float max) { _radPtc.velocityZ = tagMaxMin(min, max); _radPtc.radVelOn = true; }

	//속도 그래프
	void addVelocityGraphX(float point, float min, float max) { GraphCheck(_grpVelocityX, point, min, max); _grpVelocityX_On = true; }
	void addVelocityGraphY(float point, float min, float max) { GraphCheck(_grpVelocityY, point, min, max); _grpVelocityY_On = true; }
	void addVelocityGraphZ(float point, float min, float max) { GraphCheck(_grpVelocityZ, point, min, max); _grpVelocityZ_On = true; }

public:
	dxVelocityModule() {};
	~dxVelocityModule() {};
};

