#pragma once
#include "dxModule.h"
class dxCircleModule :	public dxModule
{
private:
	vector<tagDxGraph*> _grpRadius;
	bool _grpRadiusOn;

	D3DXVECTOR3 _preCircle;

	bool _autoRadiusOn;

public:
	virtual HRESULT init();
	virtual void relese();
	//virtual void InitUpdate(list<tagDxAttribute>::iterator iter);
	//virtual void ActiveUpdate(list<tagDxAttribute>::iterator iter);

	virtual void InitUpdate(vector<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(vector<tagDxAttribute>::iterator iter);

public:
	//������ ����
	void InitCircleRadiusX(float min, float max) { _radPtc.radiusInitX = tagMaxMin(min, max); _radPtc.circleX_On = true; }
	void InitCircleRadiusY(float min, float max) { _radPtc.radiusInitY = tagMaxMin(min, max); _radPtc.circleY_On = true; }
	void InitCircleRadiusZ(float min, float max) { _radPtc.radiusInitZ = tagMaxMin(min, max); _radPtc.circleZ_On = true; }

	//������ ������
	void InitCircleRadiusEndX(float min, float max) { _radPtc.radiusEndX = tagMaxMin(min, max); _radPtc.radiusEndX_On = true; }
	void InitCircleRadiusEndY(float min, float max) { _radPtc.radiusEndY = tagMaxMin(min, max); _radPtc.radiusEndY_On = true; }
	void InitCircleRadiusEndZ(float min, float max) { _radPtc.radiusEndZ = tagMaxMin(min, max); _radPtc.radiusEndZ_On = true; }

	//������ �׷���
	void addRadiusGraph(float point, float min, float max) { GraphCheck(_grpRadius, point, min, max); _grpRadiusOn = true; }

	//���� ���ǵ�
	void InitCircleAngleSpeedX(float min, float max) { _radPtc.circleAngleSpeedX = tagMaxMin(min, max); _radPtc.circleX_On = true; }
	void InitCircleAngleSpeedY(float min, float max) { _radPtc.circleAngleSpeedY = tagMaxMin(min, max); _radPtc.circleY_On = true; }
	void InitCircleAngleSpeedZ(float min, float max) { _radPtc.circleAngleSpeedZ = tagMaxMin(min, max); _radPtc.circleZ_On = true; }

	//���� ����
	void InitCircleStartAngleX(float min, float max) { _radPtc.circleStartAngleX = tagMaxMin(min, max); _radPtc.circleX_On = true; }
	void InitCircleStartAngleY(float min, float max) { _radPtc.circleStartAngleY = tagMaxMin(min, max); _radPtc.circleY_On = true; }
	void InitCircleStartAngleZ(float min, float max) { _radPtc.circleStartAngleZ = tagMaxMin(min, max); _radPtc.circleZ_On = true; }

	void autoRadiusOn() { _autoRadiusOn = true; };

public:
	dxCircleModule() {};
	~dxCircleModule() {};
};

