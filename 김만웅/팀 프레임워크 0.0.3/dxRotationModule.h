#pragma once
#include "dxModule.h"
class dxRotationModule : public dxModule
{
private:

public:
	virtual HRESULT init();
	virtual void relese();
	virtual void InitUpdate(vector<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(vector<tagDxAttribute>::iterator iter);

public:
	//ȸ������ ����
	void InitRotateStartAngleX(float min, float max) { _radPtc.rotateInitX = RadianMinMax(min, max); _radPtc.rotateInitX_On = true; }
	void InitRotateStartAngleY(float min, float max) { _radPtc.rotateInitY = RadianMinMax(min, max); _radPtc.rotateInitY_On = true; }
	void InitRotateStartAngleZ(float min, float max) { _radPtc.rotateInitZ = RadianMinMax(min, max); _radPtc.rotateInitZ_On = true; }

	//ȸ������ ���ǵ�
	void InitRotateAngleSpeedX(float min, float max) { _radPtc.rotateSpeedX = RadianMinMax(min, max); _radPtc.rotateSpeedX_On = true; }
	void InitRotateAngleSpeedY(float min, float max) { _radPtc.rotateSpeedY = RadianMinMax(min, max); _radPtc.rotateSpeedY_On = true; }
	void InitRotateAngleSpeedZ(float min, float max) { _radPtc.rotateSpeedZ = RadianMinMax(min, max); _radPtc.rotateSpeedZ_On = true; }

public:
	dxRotationModule() {};
	~dxRotationModule() {};

public:
	//���� �ּ��ִ밪
	tagMaxMin RadianMinMax(float inMin, float inMax)
	{
		return tagMaxMin(D3DXToRadian(inMin), D3DXToRadian(inMax));
	}

};

