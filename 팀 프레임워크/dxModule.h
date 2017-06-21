#pragma once
#include "dxParticle.h"

class dxModule
{
protected:
	
	tagDxAttributeMaxMin _radPtc;
	//vector<tagDxGraph*>::iterator _gIter;->�Ⱦ�

	//vector<tagDxAttribute*> _vPtrGraph;
	//vector<tagDxAttribute>::iterator _gIter;

	/*vector<tagDxGraph*> _grpAlpha;
	bool _grpAlphaOn;*/

	/*vector<tagDxGraph*> _grpSize;
	bool _grpSizeOn;*/

	/*vector<tagDxGraph*> _grpRadius;
	bool _grpRadiusOn;*/

	/*vector<tagDxGraph*> _grpColorR;
	vector<tagDxGraph*> _grpColorG;
	vector<tagDxGraph*> _grpColorB;
	bool _grpColorR_On;
	bool _grpColorG_On;
	bool _grpColorB_On;*/


	/*vector<tagDxGraph*> _grpVelocityX;
	vector<tagDxGraph*> _grpVelocityY;
	vector<tagDxGraph*> _grpVelocityZ;
	bool _grpVelocityX_On;
	bool _grpVelocityY_On;
	bool _grpVelocityZ_On;*/


	/*vector<tagDxGraph*> _grpPosDirectionVel;
	bool _grpPosDirectionVelOn;*/

	

	PTC_POSITION_TYPE PositionType;

	

public:
	virtual HRESULT init();
	virtual void relese();
	/*virtual void InitUpdate(list<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(list<tagDxAttribute>::iterator iter);*/
	virtual void InitUpdate(vector<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(vector<tagDxAttribute>::iterator iter);

public:
	////��ġ Ÿ�� ����
	//void SetPositionType(PTC_POSITION_TYPE posType) { PositionType = posType; }
	//void InitRandomPosSphereRadius(float min, float max) { _radPtc.posSphereRadius = tagMaxMin(min, max); }


	////��ġ
	//void InitRandomPositionX(float min, float max) { _radPtc.positionX = tagMaxMin(min, max); _radPtc.radPosOn = true; }
	//void InitRandomPositionY(float min, float max) { _radPtc.positionY = tagMaxMin(min, max); _radPtc.radPosOn = true; }
	//void InitRandomPositionZ(float min, float max) { _radPtc.positionZ = tagMaxMin(min, max); _radPtc.radPosOn = true; }

	//void InitRandomPosDirectionVelocity(float min, float max) { _radPtc.posDirectionVel = tagMaxMin(min, max); _radPtc.radPosDirectionVelOn = true; };

	//�ӵ�
	/*void InitRandomVelocityX(float min, float max) { _radPtc.velocityX = tagMaxMin(min, max); _radPtc.radVelOn = true; }
	void InitRandomVelocityY(float min, float max) { _radPtc.velocityY = tagMaxMin(min, max); _radPtc.radVelOn = true; }
	void InitRandomVelocityZ(float min, float max) { _radPtc.velocityZ = tagMaxMin(min, max); _radPtc.radVelOn = true; }*/
	//���⼺ �ӵ�->�̰� ����� ������ ���Ⱚ�� ������
	//void InitRandomDirectionVelocity(float min, float max) { _radPtc.directonVel = tagMaxMin(min, max); _radPtc.radDirectionVelOn = true; };
	

	//�ʱ��
	/*void InitRandomColorR(float min, float max) { _radPtc.colorInitR = tagMaxMin(min, max); _radPtc.radColorOn = true; }
	void InitRandomColorG(float min, float max) { _radPtc.colorInitG = tagMaxMin(min, max); _radPtc.radColorOn = true; }
	void InitRandomColorB(float min, float max) { _radPtc.colorInitB = tagMaxMin(min, max); _radPtc.radColorOn = true; }*/

	//���ӵ�
	/*void InitRandomAccelerationX(float min, float max) { _radPtc.accelerationX = tagMaxMin(min, max); _radPtc.radAccelOn = true; }
	void InitRandomAccelerationY(float min, float max) { _radPtc.accelerationY = tagMaxMin(min, max); _radPtc.radAccelOn = true; }
	void InitRandomAccelerationZ(float min, float max) { _radPtc.accelerationZ = tagMaxMin(min, max); _radPtc.radAccelOn = true; }
*/
	//�� �Ҹ�
	/*void InitRandomColorFadeR(float min, float max) { _radPtc.colorFadeR = tagMaxMin(min, max); _radPtc.radColorFadeOn = true; }
	void InitRandomColorFadeG(float min, float max) { _radPtc.colorFadeG = tagMaxMin(min, max); _radPtc.radColorFadeOn = true; }
	void InitRandomColorFadeB(float min, float max) { _radPtc.colorFadeB = tagMaxMin(min, max); _radPtc.radColorFadeOn = true; }*/

	//����
	/*void InitRandomAlpha(float min, float max) { _radPtc.alphaInit = tagMaxMin(min, max); _radPtc.radAlphaInitOn = true; }
	void InitRandomAlphaFade(float min, float max) { _radPtc.alphaFade = tagMaxMin(min, max); _radPtc.radAlphaFadeOn = true; }*/
	
	//������ ����
	//void InitRandomLiftTime(float min, float max) { _radPtc.lifeTime = tagMaxMin(min, max); _radPtc.radLifeOn = true; }

	//������ ����
	//void InitRandomSize(float min, float max) { _radPtc.sizeInit = tagMaxMin(min, max); _radPtc.radSizeInitOn = true; }
	//void InitRandomSizeEnd(float min, float max) { _radPtc.sizeEnd = tagMaxMin(min, max); _radPtc.radSizeEndOn = true; }


	//���� �׷��� ����
	//void addAlphaGraph(float point, float min, float max) { GraphCheck(_grpAlpha, point, min, max); _grpAlphaOn = true; }
	//������ �׷��� ����
	//void addSizeGraph(float point, float min, float max) { GraphCheck(_grpSize, point, min, max); _grpSizeOn = true; }
	//������ �׷��� ����
	//void addRadiusGraph(float point, float min, float max) { GraphCheck(_grpRadius, point, min, max); _grpRadiusOn = true; }
	//���� �׷��� ����
	/*void addColorGraphR(float point, float min, float max) { GraphCheck(_grpColorR, point, min, max); _grpColorR_On = true; }
	void addColorGraphG(float point, float min, float max) { GraphCheck(_grpColorG, point, min, max); _grpColorG_On = true; }
	void addColorGraphB(float point, float min, float max) { GraphCheck(_grpColorB, point, min, max); _grpColorB_On = true; }*/


	//�ӵ� �׷��� ����
	/*void addVelocityGraphX(float point, float min, float max) { GraphCheck(_grpVelocityX, point, min, max); _grpVelocityX_On = true; }
	void addVelocityGraphY(float point, float min, float max) { GraphCheck(_grpVelocityY, point, min, max); _grpVelocityY_On = true; }
	void addVelocityGraphZ(float point, float min, float max) { GraphCheck(_grpVelocityZ, point, min, max); _grpVelocityZ_On = true; }*/

	//��ġ ���⼺ �ӵ� �׷��� ����
	//void addPosDirectVelGraph(float point, float min, float max) { GraphCheck(_grpPosDirectionVel, point, min, max); _grpPosDirectionVelOn = true; };
	

	//������
	//void InitRandomRadiusX(float min, float max) { _radPtc.radiusInitX = tagMaxMin(min, max); _radPtc.circleX_On = true; }
	//void InitRandomRadiusY(float min, float max) { _radPtc.radiusInitY = tagMaxMin(min, max); _radPtc.circleY_On = true; }
	//void InitRandomRadiusZ(float min, float max) { _radPtc.radiusInitZ = tagMaxMin(min, max); _radPtc.circleZ_On = true; }

	////���� ���ǵ�
	//void InitRandomAngleSpeedX(float min, float max) { _radPtc.angleSpeedX = tagMaxMin(min, max); _radPtc.circleX_On = true; }
	//void InitRandomAngleSpeedY(float min, float max) { _radPtc.angleSpeedY = tagMaxMin(min, max); _radPtc.circleY_On = true; }
	//void InitRandomAngleSpeedZ(float min, float max) { _radPtc.angleSpeedZ = tagMaxMin(min, max); _radPtc.circleZ_On = true; }
	//
	////���� ����
	//void InitRandomStartAngleX(float min, float max) { _radPtc.startAngleX = tagMaxMin(min, max); _radPtc.circleX_On = true; }
	//void InitRandomStartAngleY(float min, float max) { _radPtc.startAngleY = tagMaxMin(min, max); _radPtc.circleY_On = true; }
	//void InitRandomStartAngleZ(float min, float max) { _radPtc.startAngleZ = tagMaxMin(min, max); _radPtc.circleZ_On = true; }

	////������ ������
	//void InitRandomRadiusEndX(float min, float max) { _radPtc.radiusEndX = tagMaxMin(min, max); _radPtc.radiusEndX_On = true; }
	//void InitRandomRadiusEndY(float min, float max) { _radPtc.radiusEndY = tagMaxMin(min, max); _radPtc.radiusEndY_On = true; }
	//void InitRandomRadiusEndZ(float min, float max) { _radPtc.radiusEndZ = tagMaxMin(min, max); _radPtc.radiusEndZ_On = true; }


	//void InitRandomRotationY(float min, float max) { _radPtc.angleSpee};
	//void InitConstPosition(D3DXVECTOR3 pos);
	//void InitConstPosition(float posX, float posY, float posZ);

public:
	dxModule() {};
	~dxModule() {};

public:
	//���� ��������
	D3DXCOLOR ColorLerp(D3DXCOLOR & from, D3DXCOLOR & to, float t)
	{
		D3DXCOLOR result(
			Lerp(from.r, to.r, t),
			Lerp(from.g, to.g, t),
			Lerp(from.b, to.b, t),
			1.0f);
		return result;
	}
	//�÷��� ������ ����Լ�
	/*float OneColorInIntOutFloat(int OneColor)
	{
		float OneColorF = OneColor / 255.0f;

		return OneColorF;
	}*/

	float OneColorF(int OneColor)
	{
		float OneColorF = OneColor / 255.0f;

		return OneColorF;
	}

	//�ΰ��� �� �ϳ�
	int RandomTwoNum(int min, int max)
	{
		int result;
		while (true)
		{
			result = RandomIntRange(min, max);
			if (result == min || result == max) { break; }
		}
		return result;
	}

protected:
	void GraphCheck(vector<tagDxGraph*>& inGraph, float point, float min,float max)
	{
		if (inGraph.empty()) inGraph.push_back(new tagDxGraph(0.0f,0.0f,0.0f));
		inGraph.push_back(new tagDxGraph(point, min, max));
	}

	void SetGraph(vector<tagDxGraph*>& inGraph)
	{
		for (int i = 1; i < inGraph.size(); i++)
		{
			inGraph[i]->value = RandomFloatRange(inGraph[i]->radValue.Min, inGraph[i]->radValue.Max);
		}
		
	}


	void GraphUpdate(vector<tagDxGraph*>& inGraph, vector<tagDxAttribute>::iterator iter, float& outValue)
	{
		for (int i = 0; i < inGraph.size() - 1; i++)
		{
			if ((iter->age / iter->lifeTime) <= inGraph[i + 1]->point)
			{
				//��ġ ���
				float currentPoint = (iter->age / iter->lifeTime - inGraph[i]->point) / (inGraph[i + 1]->point - inGraph[i]->point);
				outValue = Lerp(inGraph[i]->value, inGraph[i + 1]->value, currentPoint);
				break;
			}
		}
	}

	void GraphVelocityUpdate(vector<tagDxGraph*>& inGraph, vector<tagDxAttribute>::iterator iter, float& outValue)
	{
		//������ 1����
		for (int i = 1; i < inGraph.size(); i++)
		{
			if ((iter->age / iter->lifeTime) <= inGraph[i]->point)
			{
				//��ġ ���
				/*if (_radPtc.radDirectionVelOn)
				{
					outValue = inGraph[i]->value*iter->directionVel;
				}
				else
				{*/
					outValue = inGraph[i]->value;
				//}
				break;
			}
		}
	}

	//�� ���� ������ ����
	void OneCircleReset(float& angle)
	{
		if ((D3DX_PI*2) <= angle || -(D3DX_PI * 2) >= angle)
		{
			float differenceAngle = fabs(angle) - (D3DX_PI * 2);
			angle = differenceAngle;
		}
	}

};

