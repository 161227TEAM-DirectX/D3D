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
	//��ġ Ÿ��
	void SetPositionType(PTC_POSITION_TYPE posType) { PositionType = posType; }
	void InitRandomPosSphereRadius(float min, float max) { _radPtc.posSphereRadius = tagMaxMin(min, max); }

	//��ġ
	void InitRandomPositionX(float min, float max) { _radPtc.positionX = tagMaxMin(min, max); _radPtc.radPosOn = true; }
	void InitRandomPositionY(float min, float max) { _radPtc.positionY = tagMaxMin(min, max); _radPtc.radPosOn = true; }
	void InitRandomPositionZ(float min, float max) { _radPtc.positionZ = tagMaxMin(min, max); _radPtc.radPosOn = true; }

	//��ġ ���⼺ �ӵ�
	void InitRandomPosDirectionVelocity(float min, float max) { _radPtc.posDirectionVel = tagMaxMin(min, max); _radPtc.radPosDirectionVelOn = true; };

	//��ġ ���⼺ �ӵ� �׷���
	void addPosDirectVelGraph(float point, float min, float max) { GraphCheck(_grpPosDirectionVel, point, min, max); _grpPosDirectionVelOn = true; };
public:
	dxPositionModule() {};
	~dxPositionModule() {};
};

