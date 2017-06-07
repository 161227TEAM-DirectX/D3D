#include "stdafx.h"
#include "dxRotationModule.h"

HRESULT dxRotationModule::init()
{
	return S_OK;
}

void dxRotationModule::relese()
{
}

void dxRotationModule::InitUpdate(vector<tagDxAttribute>::iterator iter)
{
	//시작 각도 세팅
	if (_radPtc.rotateInitX_On) { iter->rotateAngle.x = RandomFloatRange(_radPtc.rotateInitX.Min, _radPtc.rotateInitX.Max); }
	if (_radPtc.rotateInitY_On) { iter->rotateAngle.y = RandomFloatRange(_radPtc.rotateInitY.Min, _radPtc.rotateInitY.Max); }
	if (_radPtc.rotateInitZ_On) { iter->rotateAngle.z = RandomFloatRange(_radPtc.rotateInitZ.Min, _radPtc.rotateInitZ.Max); }

	//각도 스피드
	if (_radPtc.rotateSpeedX_On) { iter->rotateAngleSpeed.x = RandomFloatRange(_radPtc.rotateSpeedX.Min, _radPtc.rotateSpeedX.Max); }
	if (_radPtc.rotateSpeedY_On) { iter->rotateAngleSpeed.y = RandomFloatRange(_radPtc.rotateSpeedY.Min, _radPtc.rotateSpeedY.Max); }
	if (_radPtc.rotateSpeedZ_On) { iter->rotateAngleSpeed.z = RandomFloatRange(_radPtc.rotateSpeedZ.Min, _radPtc.rotateSpeedZ.Max); }

}

void dxRotationModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{
	if (_radPtc.rotateSpeedX_On) { iter->rotateAngle.x += iter->rotateAngleSpeed.x; }
	if (_radPtc.rotateSpeedY_On) { iter->rotateAngle.y += iter->rotateAngleSpeed.y; }
	if (_radPtc.rotateSpeedZ_On) { iter->rotateAngle.z += iter->rotateAngleSpeed.z; }


	//한바퀴 돌고 리셋
	OneCircleReset(iter->rotateAngle.x);
	OneCircleReset(iter->rotateAngle.y);
	OneCircleReset(iter->rotateAngle.z);

}
