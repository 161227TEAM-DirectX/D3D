#include "stdafx.h"
#include "dxModule.h"

HRESULT dxModule::init()
{
	//초기화
//	_grpAlphaOn = false;
	//_grpSizeOn = false;
	
	/*_grpColorR_On = false;
	_grpColorG_On = false;
	_grpColorB_On = false;*/
	//_radPtc.radDirectionVelOn = false;
	//_radPtc.radPosDirectionVelOn = false;
	//_grpPosDirectionVelOn = false;
//	PositionType = PTC_DEFAULT;

	return S_OK;
}

void dxModule::relese()
{
	/*for (int i = 0; i < _grpAlpha.size(); i++)
	{
		_grpAlpha.erase(_grpAlpha.begin() + i);
	}
	_grpAlpha.clear();*/
}

//
void dxModule::InitUpdate(vector<tagDxAttribute>::iterator iter)
{
	////위치
	//if (_radPtc.radPosOn)
	//{
	//	iter->position.x = RandomFloatRange(_radPtc.positionX.Min, _radPtc.positionX.Max);
	//	iter->position.y = RandomFloatRange(_radPtc.positionY.Min, _radPtc.positionY.Max);
	//	iter->position.z = RandomFloatRange(_radPtc.positionZ.Min, _radPtc.positionZ.Max);

	//	if (PositionType == PTC_SPHERE)
	//	{
	//		D3DXVec3Normalize(&iter->position, &iter->position);

	//		//랜덤거리
	//		float radDistance = RandomFloatRange(_radPtc.posSphereRadius.Min, _radPtc.posSphereRadius.Max);
	//	
	//		//추가위치
	//		iter->position = iter->position * radDistance;

	//	}
	//
	//}

	////위치 방향성 속도
	//if (_radPtc.radPosDirectionVelOn)
	//{
	//	//방향만 뽑기
	//	//D3DXVECTOR3 posDirtion;
	//	D3DXVec3Normalize(&iter->posDirection, &iter->position);
	//	//속도
	//	iter->posDirectSpeed = RandomFloatRange(_radPtc.posDirectionVel.Min, _radPtc.posDirectionVel.Max);
	//	//iter->posDirectVel = iter->posDirection* iter->posDirectSpeed;

	//	if (_grpPosDirectionVelOn) { _grpPosDirectionVel[0]->value = iter->posDirectSpeed; }

	//}
	//if (_grpPosDirectionVelOn) { this->SetGraph(_grpPosDirectionVel); }


	//속도
	//if (_radPtc.radVelOn)
	//{
	//	iter->velocity.x = RandomFloatRange(_radPtc.velocityX.Min, _radPtc.velocityX.Max);
	//	iter->velocity.y = RandomFloatRange(_radPtc.velocityY.Min, _radPtc.velocityY.Max);
	//	iter->velocity.z = RandomFloatRange(_radPtc.velocityZ.Min, _radPtc.velocityZ.Max);


	//	//if (_radPtc.radDirectionVelOn)
	//	//{
	//	//	//방향만 뽑기
	//	//	D3DXVec3Normalize(&iter->velocity, &iter->velocity);
	//	//	//속도
	//	//	iter->directionVel = RandomFloatRange(_radPtc.directonVel.Min, _radPtc.directonVel.Max);
	//	//	iter->velocity = iter->velocity* iter->directionVel;
	//	//}

	//	

	//	if (_grpVelocityX_On) { _grpVelocityX[0]->value = iter->velocity.x; }
	//	if (_grpVelocityY_On) { _grpVelocityY[0]->value = iter->velocity.y; }
	//	if (_grpVelocityZ_On) { _grpVelocityZ[0]->value = iter->velocity.z; }

	//}
	//if (_grpVelocityX_On) { this->SetGraph(_grpVelocityX); }
	//if (_grpVelocityY_On) { this->SetGraph(_grpVelocityY); }
	//if (_grpVelocityZ_On) { this->SetGraph(_grpVelocityZ); }
	

	////색
	//if (_radPtc.radColorOn)
	//{
	//	iter->colorInit.r = RandomFloatRange(_radPtc.colorInitR.Min, _radPtc.colorInitR.Max);
	//	iter->colorInit.g = RandomFloatRange(_radPtc.colorInitG.Min, _radPtc.colorInitG.Max);
	//	iter->colorInit.b = RandomFloatRange(_radPtc.colorInitB.Min, _radPtc.colorInitB.Max);
	//	iter->colorInit.a = 1.0f;
	//	//색 세팅
	//	iter->color = iter->colorInit;
	//}

	////색 소멸
	//if (_radPtc.radColorFadeOn)
	//{
	//	iter->colorFade.r = RandomFloatRange(_radPtc.colorFadeR.Min, _radPtc.colorFadeR.Max);
	//	iter->colorFade.g = RandomFloatRange(_radPtc.colorFadeG.Min, _radPtc.colorFadeG.Max);
	//	iter->colorFade.b = RandomFloatRange(_radPtc.colorFadeB.Min, _radPtc.colorFadeB.Max);
	//}

	////알파 초기화
	//if (_radPtc.radAlphaInitOn)
	//{
	//	iter->colorInit.a = RandomFloatRange(_radPtc.alphaInit.Min, _radPtc.alphaInit.Max);
	//	iter->color.a = iter->colorInit.a;
	//	if (_grpAlphaOn) _grpAlpha[0]->value = iter->colorInit.a;//그래프용 알파
	//}
	////알파 소멸
	//if (_radPtc.radAlphaFadeOn)
	//{
	//	iter->colorFade.a = RandomFloatRange(_radPtc.alphaFade.Min, _radPtc.alphaFade.Max);
	//	//iter->color.a = iter->colorFade.a;
	//}
	////알파 그래프
	//else if (_grpAlphaOn)
	//{
	//	this->SetGraph(_grpAlpha);

	//	/*for (int i = 1; i < _grpAlpha.size(); i++)
	//	{
	//		_grpAlpha[i]->value = RandomFloatRange(_grpAlpha[i]->radValue.Min, _grpAlpha[i]->radValue.Max);
	//	}*/
	//}

	//생명
	/*if (_radPtc.radLifeOn)
	{
		iter->lifeTime = RandomFloatRange(_radPtc.lifeTime.Min, _radPtc.lifeTime.Max);
	}*/
	////가속도
	//if (_radPtc.radAccelOn)
	//{
	//	iter->acceleration.x = RandomFloatRange(_radPtc.accelerationX.Min, _radPtc.accelerationX.Max);
	//	iter->acceleration.y = RandomFloatRange(_radPtc.accelerationY.Min, _radPtc.accelerationY.Max);
	//	iter->acceleration.z = RandomFloatRange(_radPtc.accelerationZ.Min, _radPtc.accelerationZ.Max);
	//}
	//사이즈
	//if (_radPtc.radSizeInitOn)
	//{
	//	iter->sizeInit = RandomFloatRange(_radPtc.sizeInit.Min, _radPtc.sizeInit.Max);
	//	iter->size = iter->sizeInit;
	//	if (_grpSizeOn) _grpSize[0]->value = iter->sizeInit;//그래프용 사이즈
	//}
	//if (_grpSizeOn)
	//{
	//	this->SetGraph(_grpSize);
	//}

	//if (_radPtc.radSizeEndOn)
	//{
	//	iter->sizeEnd = RandomFloatRange(_radPtc.sizeEnd.Min, _radPtc.sizeEnd.Max);
	//}

	////원형 돌기 초기화
	//if (_radPtc.circleX_On)
	//{
	//	iter->angle.x = D3DXToRadian(RandomFloatRange(_radPtc.startAngleX.Min, _radPtc.startAngleX.Max));
	//	iter->angleSpeed.x = RandomFloatRange(_radPtc.angleSpeedX.Min, _radPtc.angleSpeedX.Max);
	//	iter->radiusInit.x = RandomFloatRange(_radPtc.radiusInitX.Min, _radPtc.radiusInitX.Max);
	//	iter->radius.x = iter->radiusInit.x;
	//}
	//if (_radPtc.circleY_On)
	//{
	//	iter->angle.y = D3DXToRadian(RandomFloatRange(_radPtc.startAngleY.Min, _radPtc.startAngleY.Max));
	//	iter->angleSpeed.y = RandomFloatRange(_radPtc.angleSpeedY.Min, _radPtc.angleSpeedY.Max);
	//	iter->radiusInit.y = RandomFloatRange(_radPtc.radiusInitY.Min, _radPtc.radiusInitY.Max);
	//	iter->radius.y = iter->radiusInit.y;
	//}
	//if (_radPtc.circleZ_On)
	//{
	//	iter->angle.z = D3DXToRadian(RandomFloatRange(_radPtc.startAngleZ.Min, _radPtc.startAngleZ.Max));
	//	iter->angleSpeed.z = RandomFloatRange(_radPtc.angleSpeedZ.Min, _radPtc.angleSpeedZ.Max);
	//	iter->radiusInit.z = RandomFloatRange(_radPtc.radiusInitZ.Min, _radPtc.radiusInitZ.Max);
	//	iter->radius.z = iter->radiusInit.z;
	//}

	//if (_radPtc.radiusEndX_On) { iter->radiusEnd.x = RandomFloatRange(_radPtc.radiusEndX.Min, _radPtc.radiusEndX.Max); }
	//if (_radPtc.radiusEndY_On) { iter->radiusEnd.y = RandomFloatRange(_radPtc.radiusEndY.Min, _radPtc.radiusEndY.Max);}
	//if (_radPtc.radiusEndZ_On) { iter->radiusEnd.z = RandomFloatRange(_radPtc.radiusEndZ.Min, _radPtc.radiusEndZ.Max);}

	////앵글 스피드 초기화
	//iter->circleSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


//
void dxModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{
	////색깔
	//if (_radPtc.radColorFadeOn)
	//{
	//	iter->color = ColorLerp(iter->colorInit, iter->colorFade, (iter->age / iter->lifeTime));
	//}
	////색깔 그래프
	//else
	//{
	//	if (_grpColorR_On) { this->GraphUpdate(_grpColorR, iter, iter->color.r); }
	//	if (_grpColorG_On) { this->GraphUpdate(_grpColorG, iter, iter->color.g); }
	//	if (_grpColorB_On) { this->GraphUpdate(_grpColorB, iter, iter->color.b); }
	//}
	////알파값
	//if (_radPtc.radAlphaFadeOn)
	//{
	//	iter->color.a = Lerp(iter->colorInit.a, iter->colorFade.a, (iter->age / iter->lifeTime));
	//}
	////알파 그래프
	//else if (_grpAlphaOn)
	//{
	//	this->GraphUpdate(_grpAlpha,iter,iter->color.a);
	//}
	


	////사이즈 조절
	//if (_radPtc.radSizeEndOn)
	//{
	//	iter->size = Lerp(iter->sizeInit, iter->sizeEnd, (iter->age / iter->lifeTime));
	//	//iter->size = Lerp(1.0f, 12.0f, (iter->age / iter->lifeTime));
	//}
	////사이즈 그래프
	//else if (_grpSizeOn)
	//{
	//	this->GraphUpdate(_grpSize, iter, iter->size);
	//}

	////원을 돌려보자
	//D3DXVECTOR3 circleRotX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3	circleRotY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3	circleRotZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////원 계산
	//circleRotX = D3DXVECTOR3(0.0f ,cosf(iter->angle.x) * iter->radius.x, sinf(iter->angle.x) * iter->radius.x);
	//circleRotY = D3DXVECTOR3(cosf(iter->angle.y) * iter->radius.y, 0.0f, sinf(iter->angle.y) * iter->radius.y);
	//circleRotZ = D3DXVECTOR3(cosf(iter->angle.z) * iter->radius.z, sinf(iter->angle.z) * iter->radius.z, 0.0f);

	////원 계산 적용
	//iter->circleSpeed = circleRotX + circleRotY + circleRotZ;

	////반지름 선형보간
	//if (_radPtc.radiusEndX_On) { iter->radius.x = Lerp(iter->radiusInit.x, iter->radiusEnd.x, (iter->age / iter->lifeTime)); }
	//if (_radPtc.radiusEndY_On) { iter->radius.y = Lerp(iter->radiusInit.y, iter->radiusEnd.y, (iter->age / iter->lifeTime)); }
	//if (_radPtc.radiusEndZ_On) { iter->radius.z = Lerp(iter->radiusInit.z, iter->radiusEnd.z, (iter->age / iter->lifeTime)); }

	////각도 적용
	//if (_radPtc.circleX_On) iter->angle.x += D3DXToRadian(iter->angleSpeed.x)*_timeDelta;
	//if (_radPtc.circleY_On) iter->angle.y += D3DXToRadian(iter->angleSpeed.y)*_timeDelta;
	//if (_radPtc.circleZ_On) iter->angle.z += D3DXToRadian(iter->angleSpeed.z)*_timeDelta;



	////한바퀴 돌고 리셋
	//OneCircleReset(iter->angle.x);
	//OneCircleReset(iter->angle.y);
	//OneCircleReset(iter->angle.z);


	//속도->잘못됐지만 써먹을 수 있을 거라 믿음
	/*if (_grpVelocityX_On) { this->GraphUpdate(_grpVelocityX, iter, iter->velocity.x); }
	if (_grpVelocityY_On) { this->GraphUpdate(_grpVelocityY, iter, iter->velocity.y); }
	if (_grpVelocityZ_On) { this->GraphUpdate(_grpVelocityZ, iter, iter->velocity.z); }*/

	////속도
	//if (_grpVelocityX_On) { this->GraphVelocityUpdate(_grpVelocityX, iter, iter->velocity.x); }
	//if (_grpVelocityY_On) { this->GraphVelocityUpdate(_grpVelocityY, iter, iter->velocity.y); }
	//if (_grpVelocityZ_On) { this->GraphVelocityUpdate(_grpVelocityZ, iter, iter->velocity.z); }

	//if (_grpPosDirectionVelOn)
	//{
	//	this->GraphVelocityUpdate(_grpPosDirectionVel, iter, iter->posDirectSpeed);
	//	iter->posDirectVel = iter->posDirection*iter->posDirectSpeed;
	//}


}
