#pragma once
#include "dxParticle.h"

class dxModule
{
protected:

	tagDxAttributeMaxMin _radPtc;

	//위치타입
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
	//벡터 선형보간
	D3DXCOLOR ColorLerp(D3DXCOLOR & from, D3DXCOLOR & to, float t)
	{
		D3DXCOLOR result(
			Lerp(from.r, to.r, t),
			Lerp(from.g, to.g, t),
			Lerp(from.b, to.b, t),
			1.0f);
		return result;
	}
	//컬러값 정수형 계산함수
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

	//두가지 중 하나
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
	//그래프 체크
	void GraphCheck(vector<tagDxGraph*>& inGraph, float point, float min, float max)
	{
		if (inGraph.empty()) inGraph.push_back(new tagDxGraph(0.0f, 0.0f, 0.0f));
		inGraph.push_back(new tagDxGraph(point, min, max));
	}

	//그래프 세팅
	void SetGraph(vector<tagDxGraph*>& inGraph)
	{
		for (int i = 1; i < inGraph.size(); i++)
		{
			inGraph[i]->value = RandomFloatRange(inGraph[i]->radValue.Min, inGraph[i]->radValue.Max);
		}

	}

	//그래프 업데이트
	void GraphUpdate(vector<tagDxGraph*>& inGraph, vector<tagDxAttribute>::iterator iter, float& outValue)
	{
		for (int i = 0; i < inGraph.size() - 1; i++)
		{
			if ((iter->age / iter->lifeTime) <= inGraph[i + 1]->point)
			{
				//위치 계산
				float currentPoint = (iter->age / iter->lifeTime - inGraph[i]->point) / (inGraph[i + 1]->point - inGraph[i]->point);
				outValue = Lerp(inGraph[i]->value, inGraph[i + 1]->value, currentPoint);
				break;
			}
		}
	}

	void GraphVelocityUpdate(vector<tagDxGraph*>& inGraph, vector<tagDxAttribute>::iterator iter, float& outValue)
	{
		//시작이 1부터
		for (int i = 1; i < inGraph.size(); i++)
		{
			if ((iter->age / iter->lifeTime) <= inGraph[i]->point)
			{
				//위치 계산
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

	//한 바퀴 돌리고 리셋
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

