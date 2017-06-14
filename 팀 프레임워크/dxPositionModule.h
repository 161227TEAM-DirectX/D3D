#pragma once
#include "dxModule.h"
class dxPositionModule :public dxModule
{
private:
	vector<tagDxGraph*> _grpPosDirectionVel;
	bool _grpPosDirectionVelOn;
public:
	virtual HRESULT init();
	virtual void relese();
	//virtual void InitUpdate(list<tagDxAttribute>::iterator iter);
	//virtual void ActiveUpdate(list<tagDxAttribute>::iterator iter);

	virtual void InitUpdate(vector<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(vector<tagDxAttribute>::iterator iter);

public:
	//위치 타입
	void SetPositionType(PTC_POSITION_TYPE posType) { PositionType = posType; }
	void InitRandomPosSphereRadius(float min, float max) { _radPtc.posSphereRadius = tagMaxMin(min, max); }

	//위치
	void InitRandomPositionX(float min, float max) { _radPtc.positionX = tagMaxMin(min, max); _radPtc.radPosOn = true; }
	void InitRandomPositionY(float min, float max) { _radPtc.positionY = tagMaxMin(min, max); _radPtc.radPosOn = true; }
	void InitRandomPositionZ(float min, float max) { _radPtc.positionZ = tagMaxMin(min, max); _radPtc.radPosOn = true; }

	//위치 방향성 속도
	void InitRandomPosDirectionVelocity(float min, float max) { _radPtc.posDirectionVel = tagMaxMin(min, max); _radPtc.radPosDirectionVelOn = true; };

	//위치 방향성 속도 그래프
	void addPosDirectVelGraph(float point, float min, float max) { GraphCheck(_grpPosDirectionVel, point, min, max); _grpPosDirectionVelOn = true; };

	//구 위치 방향
	void InitDirSphere(float dirX, float dirY, float dirZ) { _radPtc.dirSphere = D3DXVECTOR3(dirX, dirY, dirZ); }

public:
	//끌림 고정
	void InitConstAttractCenter(float x, float y, float z) {_radPtc.attractX = tagMaxMin(x, x); _radPtc.attractY = tagMaxMin(y, y); _radPtc.attractZ = tagMaxMin(z, z); _radPtc.attractOn = true; };

	//끌림 램덤
	void InitAttractCenterX(float min, float max) { _radPtc.attractX = tagMaxMin(min, max); _radPtc.attractOn = true; }
	void InitAttractCenterY(float min, float max) { _radPtc.attractY = tagMaxMin(min, max); _radPtc.attractOn = true; }
	void InitAttractCenterZ(float min, float max) { _radPtc.attractZ = tagMaxMin(min, max); _radPtc.attractOn = true; }

public:
	dxPositionModule() {};
	~dxPositionModule() {};
};

