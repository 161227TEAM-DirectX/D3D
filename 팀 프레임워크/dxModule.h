#pragma once
#include "dxParticle.h"

class dxModule
{
protected:

	tagDxAttributeMaxMin _radPtc;

	//��ġŸ��
	PTC_POSITION_TYPE PositionType;
	
public:
	virtual HRESULT init();
	virtual void relese();
	/*virtual void InitUpdate(list<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(list<tagDxAttribute>::iterator iter);*/
	virtual void InitUpdate(vector<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(vector<tagDxAttribute>::iterator iter);

	;

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
	//�׷��� üũ
	void GraphCheck(vector<tagDxGraph*>& inGraph, float point, float min, float max)
	{
		if (inGraph.empty()) inGraph.push_back(new tagDxGraph(0.0f, 0.0f, 0.0f));
		inGraph.push_back(new tagDxGraph(point, min, max));
	}

	//�׷��� ����
	void SetGraph(vector<tagDxGraph*>& inGraph)
	{
		for (int i = 1; i < inGraph.size(); i++)
		{
			inGraph[i]->value = RandomFloatRange(inGraph[i]->radValue.Min, inGraph[i]->radValue.Max);
		}

	}

	//�׷��� ������Ʈ
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
		if ((D3DX_PI * 2) <= angle || -(D3DX_PI * 2) >= angle)
		{
			float differenceAngle = fabs(angle) - (D3DX_PI * 2);
			angle = differenceAngle;
		}
	}

public:
	dxModule() {};
	~dxModule() {}
};

