#include "stdafx.h"
#include "dxModule.h"

HRESULT dxModule::init()
{
	//�ʱ�ȭ
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
	////��ġ
	//if (_radPtc.radPosOn)
	//{
	//	iter->position.x = RandomFloatRange(_radPtc.positionX.Min, _radPtc.positionX.Max);
	//	iter->position.y = RandomFloatRange(_radPtc.positionY.Min, _radPtc.positionY.Max);
	//	iter->position.z = RandomFloatRange(_radPtc.positionZ.Min, _radPtc.positionZ.Max);

	//	if (PositionType == PTC_SPHERE)
	//	{
	//		D3DXVec3Normalize(&iter->position, &iter->position);

	//		//�����Ÿ�
	//		float radDistance = RandomFloatRange(_radPtc.posSphereRadius.Min, _radPtc.posSphereRadius.Max);
	//	
	//		//�߰���ġ
	//		iter->position = iter->position * radDistance;

	//	}
	//
	//}

	////��ġ ���⼺ �ӵ�
	//if (_radPtc.radPosDirectionVelOn)
	//{
	//	//���⸸ �̱�
	//	//D3DXVECTOR3 posDirtion;
	//	D3DXVec3Normalize(&iter->posDirection, &iter->position);
	//	//�ӵ�
	//	iter->posDirectSpeed = RandomFloatRange(_radPtc.posDirectionVel.Min, _radPtc.posDirectionVel.Max);
	//	//iter->posDirectVel = iter->posDirection* iter->posDirectSpeed;

	//	if (_grpPosDirectionVelOn) { _grpPosDirectionVel[0]->value = iter->posDirectSpeed; }

	//}
	//if (_grpPosDirectionVelOn) { this->SetGraph(_grpPosDirectionVel); }


	//�ӵ�
	//if (_radPtc.radVelOn)
	//{
	//	iter->velocity.x = RandomFloatRange(_radPtc.velocityX.Min, _radPtc.velocityX.Max);
	//	iter->velocity.y = RandomFloatRange(_radPtc.velocityY.Min, _radPtc.velocityY.Max);
	//	iter->velocity.z = RandomFloatRange(_radPtc.velocityZ.Min, _radPtc.velocityZ.Max);


	//	//if (_radPtc.radDirectionVelOn)
	//	//{
	//	//	//���⸸ �̱�
	//	//	D3DXVec3Normalize(&iter->velocity, &iter->velocity);
	//	//	//�ӵ�
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
	

	////��
	//if (_radPtc.radColorOn)
	//{
	//	iter->colorInit.r = RandomFloatRange(_radPtc.colorInitR.Min, _radPtc.colorInitR.Max);
	//	iter->colorInit.g = RandomFloatRange(_radPtc.colorInitG.Min, _radPtc.colorInitG.Max);
	//	iter->colorInit.b = RandomFloatRange(_radPtc.colorInitB.Min, _radPtc.colorInitB.Max);
	//	iter->colorInit.a = 1.0f;
	//	//�� ����
	//	iter->color = iter->colorInit;
	//}

	////�� �Ҹ�
	//if (_radPtc.radColorFadeOn)
	//{
	//	iter->colorFade.r = RandomFloatRange(_radPtc.colorFadeR.Min, _radPtc.colorFadeR.Max);
	//	iter->colorFade.g = RandomFloatRange(_radPtc.colorFadeG.Min, _radPtc.colorFadeG.Max);
	//	iter->colorFade.b = RandomFloatRange(_radPtc.colorFadeB.Min, _radPtc.colorFadeB.Max);
	//}

	////���� �ʱ�ȭ
	//if (_radPtc.radAlphaInitOn)
	//{
	//	iter->colorInit.a = RandomFloatRange(_radPtc.alphaInit.Min, _radPtc.alphaInit.Max);
	//	iter->color.a = iter->colorInit.a;
	//	if (_grpAlphaOn) _grpAlpha[0]->value = iter->colorInit.a;//�׷����� ����
	//}
	////���� �Ҹ�
	//if (_radPtc.radAlphaFadeOn)
	//{
	//	iter->colorFade.a = RandomFloatRange(_radPtc.alphaFade.Min, _radPtc.alphaFade.Max);
	//	//iter->color.a = iter->colorFade.a;
	//}
	////���� �׷���
	//else if (_grpAlphaOn)
	//{
	//	this->SetGraph(_grpAlpha);

	//	/*for (int i = 1; i < _grpAlpha.size(); i++)
	//	{
	//		_grpAlpha[i]->value = RandomFloatRange(_grpAlpha[i]->radValue.Min, _grpAlpha[i]->radValue.Max);
	//	}*/
	//}

	//����
	/*if (_radPtc.radLifeOn)
	{
		iter->lifeTime = RandomFloatRange(_radPtc.lifeTime.Min, _radPtc.lifeTime.Max);
	}*/
	////���ӵ�
	//if (_radPtc.radAccelOn)
	//{
	//	iter->acceleration.x = RandomFloatRange(_radPtc.accelerationX.Min, _radPtc.accelerationX.Max);
	//	iter->acceleration.y = RandomFloatRange(_radPtc.accelerationY.Min, _radPtc.accelerationY.Max);
	//	iter->acceleration.z = RandomFloatRange(_radPtc.accelerationZ.Min, _radPtc.accelerationZ.Max);
	//}
	//������
	//if (_radPtc.radSizeInitOn)
	//{
	//	iter->sizeInit = RandomFloatRange(_radPtc.sizeInit.Min, _radPtc.sizeInit.Max);
	//	iter->size = iter->sizeInit;
	//	if (_grpSizeOn) _grpSize[0]->value = iter->sizeInit;//�׷����� ������
	//}
	//if (_grpSizeOn)
	//{
	//	this->SetGraph(_grpSize);
	//}

	//if (_radPtc.radSizeEndOn)
	//{
	//	iter->sizeEnd = RandomFloatRange(_radPtc.sizeEnd.Min, _radPtc.sizeEnd.Max);
	//}

	////���� ���� �ʱ�ȭ
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

	////�ޱ� ���ǵ� �ʱ�ȭ
	//iter->circleSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


//
void dxModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{
	////����
	//if (_radPtc.radColorFadeOn)
	//{
	//	iter->color = ColorLerp(iter->colorInit, iter->colorFade, (iter->age / iter->lifeTime));
	//}
	////���� �׷���
	//else
	//{
	//	if (_grpColorR_On) { this->GraphUpdate(_grpColorR, iter, iter->color.r); }
	//	if (_grpColorG_On) { this->GraphUpdate(_grpColorG, iter, iter->color.g); }
	//	if (_grpColorB_On) { this->GraphUpdate(_grpColorB, iter, iter->color.b); }
	//}
	////���İ�
	//if (_radPtc.radAlphaFadeOn)
	//{
	//	iter->color.a = Lerp(iter->colorInit.a, iter->colorFade.a, (iter->age / iter->lifeTime));
	//}
	////���� �׷���
	//else if (_grpAlphaOn)
	//{
	//	this->GraphUpdate(_grpAlpha,iter,iter->color.a);
	//}
	


	////������ ����
	//if (_radPtc.radSizeEndOn)
	//{
	//	iter->size = Lerp(iter->sizeInit, iter->sizeEnd, (iter->age / iter->lifeTime));
	//	//iter->size = Lerp(1.0f, 12.0f, (iter->age / iter->lifeTime));
	//}
	////������ �׷���
	//else if (_grpSizeOn)
	//{
	//	this->GraphUpdate(_grpSize, iter, iter->size);
	//}

	////���� ��������
	//D3DXVECTOR3 circleRotX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3	circleRotY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3	circleRotZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////�� ���
	//circleRotX = D3DXVECTOR3(0.0f ,cosf(iter->angle.x) * iter->radius.x, sinf(iter->angle.x) * iter->radius.x);
	//circleRotY = D3DXVECTOR3(cosf(iter->angle.y) * iter->radius.y, 0.0f, sinf(iter->angle.y) * iter->radius.y);
	//circleRotZ = D3DXVECTOR3(cosf(iter->angle.z) * iter->radius.z, sinf(iter->angle.z) * iter->radius.z, 0.0f);

	////�� ��� ����
	//iter->circleSpeed = circleRotX + circleRotY + circleRotZ;

	////������ ��������
	//if (_radPtc.radiusEndX_On) { iter->radius.x = Lerp(iter->radiusInit.x, iter->radiusEnd.x, (iter->age / iter->lifeTime)); }
	//if (_radPtc.radiusEndY_On) { iter->radius.y = Lerp(iter->radiusInit.y, iter->radiusEnd.y, (iter->age / iter->lifeTime)); }
	//if (_radPtc.radiusEndZ_On) { iter->radius.z = Lerp(iter->radiusInit.z, iter->radiusEnd.z, (iter->age / iter->lifeTime)); }

	////���� ����
	//if (_radPtc.circleX_On) iter->angle.x += D3DXToRadian(iter->angleSpeed.x)*_timeDelta;
	//if (_radPtc.circleY_On) iter->angle.y += D3DXToRadian(iter->angleSpeed.y)*_timeDelta;
	//if (_radPtc.circleZ_On) iter->angle.z += D3DXToRadian(iter->angleSpeed.z)*_timeDelta;



	////�ѹ��� ���� ����
	//OneCircleReset(iter->angle.x);
	//OneCircleReset(iter->angle.y);
	//OneCircleReset(iter->angle.z);


	//�ӵ�->�߸������� ����� �� ���� �Ŷ� ����
	/*if (_grpVelocityX_On) { this->GraphUpdate(_grpVelocityX, iter, iter->velocity.x); }
	if (_grpVelocityY_On) { this->GraphUpdate(_grpVelocityY, iter, iter->velocity.y); }
	if (_grpVelocityZ_On) { this->GraphUpdate(_grpVelocityZ, iter, iter->velocity.z); }*/

	////�ӵ�
	//if (_grpVelocityX_On) { this->GraphVelocityUpdate(_grpVelocityX, iter, iter->velocity.x); }
	//if (_grpVelocityY_On) { this->GraphVelocityUpdate(_grpVelocityY, iter, iter->velocity.y); }
	//if (_grpVelocityZ_On) { this->GraphVelocityUpdate(_grpVelocityZ, iter, iter->velocity.z); }

	//if (_grpPosDirectionVelOn)
	//{
	//	this->GraphVelocityUpdate(_grpPosDirectionVel, iter, iter->posDirectSpeed);
	//	iter->posDirectVel = iter->posDirection*iter->posDirectSpeed;
	//}


}
