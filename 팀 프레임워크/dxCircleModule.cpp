#include "stdafx.h"
#include "dxCircleModule.h"


HRESULT dxCircleModule::init()
{
	_grpRadiusOn = false;

	_preCircle = D3DXVECTOR3(0, 0, 0);

	_autoRadiusOn = true;

	return S_OK;
}

void dxCircleModule::relese()
{

}

void dxCircleModule::InitUpdate(vector<tagDxAttribute>::iterator iter)
{
	//원형 돌기 초기화
	if (_radPtc.circleX_On)
	{
		iter->circleAngle.x = D3DXToRadian(RandomFloatRange(_radPtc.circleStartAngleX.Min, _radPtc.circleStartAngleX.Max));
		iter->circelAngleSpeed.x = RandomFloatRange(_radPtc.circleAngleSpeedX.Min, _radPtc.circleAngleSpeedX.Max);
		iter->radiusInit.x = RandomFloatRange(_radPtc.radiusInitX.Min, _radPtc.radiusInitX.Max);
		iter->radius.x = iter->radiusInit.x;
	}
	if (_radPtc.circleY_On)
	{
		iter->circleAngle.y = D3DXToRadian(RandomFloatRange(_radPtc.circleStartAngleY.Min, _radPtc.circleStartAngleY.Max));
		iter->circelAngleSpeed.y = RandomFloatRange(_radPtc.circleAngleSpeedY.Min, _radPtc.circleAngleSpeedY.Max);
		iter->radiusInit.y = RandomFloatRange(_radPtc.radiusInitY.Min, _radPtc.radiusInitY.Max);
		iter->radius.y = iter->radiusInit.y;
	}
	if (_radPtc.circleZ_On)
	{
		iter->circleAngle.z = D3DXToRadian(RandomFloatRange(_radPtc.circleStartAngleZ.Min, _radPtc.circleStartAngleZ.Max));
		iter->circelAngleSpeed.z = RandomFloatRange(_radPtc.circleAngleSpeedZ.Min, _radPtc.circleAngleSpeedZ.Max);
		iter->radiusInit.z = RandomFloatRange(_radPtc.radiusInitZ.Min, _radPtc.radiusInitZ.Max);
		iter->radius.z = iter->radiusInit.z;
	}

	if (_radPtc.radiusEndX_On) { iter->radiusEnd.x = RandomFloatRange(_radPtc.radiusEndX.Min, _radPtc.radiusEndX.Max); }
	if (_radPtc.radiusEndY_On) { iter->radiusEnd.y = RandomFloatRange(_radPtc.radiusEndY.Min, _radPtc.radiusEndY.Max); }
	if (_radPtc.radiusEndZ_On) { iter->radiusEnd.z = RandomFloatRange(_radPtc.radiusEndZ.Min, _radPtc.radiusEndZ.Max); }

	//앵글 스피드 초기화
	iter->circleSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void dxCircleModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{
	//원을 돌려보자
	D3DXVECTOR3 circleRotX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	circleRotY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	circleRotZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//실패
	//if (_autoRadiusOn)
	//{
	//	D3DXVECTOR3 circleDirAixsX = D3DXVECTOR3(0.0f, iter->FinalPos.y, iter->FinalPos.z);
	//	D3DXVECTOR3 circleDirAixsY = D3DXVECTOR3(iter->FinalPos.x, 0.0f, iter->FinalPos.z);
	//	D3DXVECTOR3 circleDirAixsZ = D3DXVECTOR3(iter->FinalPos.x, iter->FinalPos.y, 0.0f);
	//	
	//	D3DXVECTOR3 distanceAixs = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	distanceAixs.x = D3DXVec3Length(&circleDirAixsX);
	//	distanceAixs.y = D3DXVec3Length(&circleDirAixsY);
	//	distanceAixs.z = 2.0f; // D3DXVec3Length(&circleDirAixsZ);

	//	//원 계산
	//	circleRotX = D3DXVECTOR3(0.0f, cosf(iter->circleAngle.x) *distanceAixs.x, sinf(iter->circleAngle.x) * distanceAixs.x);
	//	circleRotY = D3DXVECTOR3(cosf(iter->circleAngle.y) * distanceAixs.y, 0.0f, sinf(iter->circleAngle.y) * distanceAixs.y);
	//	circleRotZ = D3DXVECTOR3(cosf(iter->circleAngle.z) * distanceAixs.z, sinf(iter->circleAngle.z) * distanceAixs.z, 0.0f);
	//}
	//else
	//{
		//원 계산
	circleRotX = D3DXVECTOR3(0.0f, cosf(iter->circleAngle.x) * iter->radius.x, sinf(iter->circleAngle.x) * iter->radius.x);
	circleRotY = D3DXVECTOR3(cosf(iter->circleAngle.y) * iter->radius.y, 0.0f, sinf(iter->circleAngle.y) * iter->radius.y);
	circleRotZ = D3DXVECTOR3(cosf(iter->circleAngle.z) * iter->radius.z, sinf(iter->circleAngle.z) * iter->radius.z, 0.0f);
	//}

	//전 원 계산 세팅
	iter->preCircleSpeed = iter->circleSpeed;

	//원 계산 적용
	iter->circleSpeed = circleRotX + circleRotY + circleRotZ;

	//반지름 선형보간
	if (_radPtc.radiusEndX_On) { iter->radius.x = Lerp(iter->radiusInit.x, iter->radiusEnd.x, (iter->age / iter->lifeTime)); }
	if (_radPtc.radiusEndY_On) { iter->radius.y = Lerp(iter->radiusInit.y, iter->radiusEnd.y, (iter->age / iter->lifeTime)); }
	if (_radPtc.radiusEndZ_On) { iter->radius.z = Lerp(iter->radiusInit.z, iter->radiusEnd.z, (iter->age / iter->lifeTime)); }

	//각도 적용
	if (_radPtc.circleX_On) iter->circleAngle.x += D3DXToRadian(iter->circelAngleSpeed.x) *_timeDelta*iter->emitterNum;
	if (_radPtc.circleY_On) iter->circleAngle.y += D3DXToRadian(iter->circelAngleSpeed.y) *_timeDelta*iter->emitterNum;
	if (_radPtc.circleZ_On) iter->circleAngle.z += D3DXToRadian(iter->circelAngleSpeed.z) *_timeDelta*iter->emitterNum;

	//if (_radPtc.circleX_On || _radPtc.circleY_On || _radPtc.circleZ_On)
	//{
	//	//iter->circleAngle = iter->circleAngle*_timeDelta;
	//}

	//한바퀴 돌고 리셋
	OneCircleReset(iter->circleAngle.x);
	OneCircleReset(iter->circleAngle.y);
	OneCircleReset(iter->circleAngle.z);
}
