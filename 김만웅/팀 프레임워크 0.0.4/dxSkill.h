#pragma once
#include "dxParticleSystem.h"
#include "transform.h"

class dxSkill
{
protected:
	enum SKILL_RENDER_TYPE
	{
		SR_One,
		SR_Array,
		SR_Custom
	
	};

#define SR_One		SR_One
#define	SR_Array	SR_Array
#define SR_Custom	SR_Custom
protected:
	//렌더 타입 선언부
	SKILL_RENDER_TYPE _SkillRenderType;



	//트렌스폼
	dx::transform* _playerTrans;
	dx::transform* _actionTrans;
	dx::transform* _targetTrans;

	//시작 불값
	bool _skillStartOn;
	bool _skillPrepareOn;
	bool _skillActionOn;
	bool _skillFinshOn;
	bool _skillResetOn;

	//파티클 시스템
	dxParticleSystem* _preparePS;
	dxParticleSystem* _actionPS;
	dxParticleSystem* _finishPS;

	//파티클 시스템 벡터
	vector<dxParticleSystem*> _vPrepaerPS;
	vector<dxParticleSystem*> _vActionPS;
	vector<dxParticleSystem*> _vFinishPS;

	//파티클 시스템 배열
	/*dxParticleSystem* _arrayPreparePS;
	dxParticleSystem* _arrayActionPS;
	dxParticleSystem* _arrayFinishPS;*/

	//파티클 시스템 배열개수
	int _PrepareSize;
	int _ActionSize;
	int _FinishSize;

	boundSphere* _actionSphereCollision;
	boundSphere* _targetSphereCollision;

	//마지막 시간
	float _resetTime;
	float _currentResetTime;
	
	//디폴트 렌더 여부
	//bool _defualtRendrOn;

public:
	virtual HRESULT init();
	virtual void release();
	//virtual void update(transform* playerTrans, transform* tagetTrans) = 0;
	//virtual void update(transform* playerTrans, transform* tagetTrans);
	void update();	//NO버츄얼....부모가 업데이트함.
	void render();

public:
	//동작 시작
	void Start() { _skillStartOn = true; }
	//업데이트 동작
	virtual bool Prepare() = 0;
	virtual bool Action() = 0;
	virtual void Finsh() = 0;
	virtual void Reset() = 0;

public:
	//렌더 동작
	virtual void RenderPrepare() { }
	virtual void RenderAction() { }
	virtual void RenderFinsh() { }

public:
	virtual void setPlayer(dx::transform* inPlayerTrans) { _playerTrans = inPlayerTrans; };
	virtual void setTarget(dx::transform* inTargetTrans) { _targetTrans = inTargetTrans; };
	//virtual void setAction(transform* inTargetTrans) { _actionTrans = inTargetTrans; };

	void setPreparePS(string psName) { PSM->initPS(_preparePS, psName); }
	void setActionPS(string psName)  { PSM->initPS(_actionPS, psName); }
	void setFinishPS(string psName)  { PSM->initPS(_finishPS, psName); }

	void setArrayPreparePS(string psName, int arrayNum) { PSM->initArrayPS(_vPrepaerPS, arrayNum, psName); }
	void setArrayActionPS(string psName, int arrayNum) { PSM->initArrayPS(_vActionPS, arrayNum, psName); }
	void setArrayFinishPS(string psName, int arrayNum) { PSM->initArrayPS(_vFinishPS, arrayNum, psName); }
	
protected:
	//베지어 곡선용
	struct tagBezierPoint
	{
		D3DXVECTOR3 P0;
		D3DXVECTOR3 P1;
		D3DXVECTOR3 P2;
		D3DXVECTOR3 P3;

		tagBezierPoint()
		{
			P0 = P1 = P2 = P3 = D3DXVECTOR3(0,0,0);
		}
	};

	int RandomTwoNum(int min,int max)
	{
		int result;
		while (true)
		{
			result = RandomIntRange(min, max);
			if (result == min || result == max) { break; }
		}
		return result;
	}

	//3차 베지어 곡선 공식
	D3DXVECTOR3 BezierP3Cube(D3DXVECTOR3 P0, D3DXVECTOR3 P1, D3DXVECTOR3 P2, D3DXVECTOR3 P3,float timePos, D3DXVECTOR3& outBP = D3DXVECTOR3(0,0,0))
	{
		D3DXVECTOR3 BezierPoint;

		BezierPoint = P0*powf((1.0f - timePos), 3) + 3 * P1*timePos*powf((1.0f - timePos), 2) + 3 * P2*powf(timePos, 2)*(1.0f - timePos) + P3*powf(timePos, 3);
		outBP = BezierPoint;

		return BezierPoint;
	}
	D3DXVECTOR3 BezierP3Cube(tagBezierPoint inBP, float timePos, D3DXVECTOR3& outBP = D3DXVECTOR3(0, 0, 0))
	{
		D3DXVECTOR3 BezierPoint;

		BezierPoint = inBP.P0*powf((1.0f - timePos), 3) + 3.0f * inBP.P1*timePos*powf((1.0f - timePos), 2) + 3.0f * inBP.P2*powf(timePos, 2)*(1.0f - timePos) + inBP.P3*powf(timePos, 3);
		outBP = BezierPoint;

		return BezierPoint;
	}


public:
	//생성자
	dxSkill()
	{
		//동작들 초기화
		_skillStartOn = false;
		_skillActionOn = false;
		_skillFinshOn = false;
		_skillResetOn = false;
		//시간 초기화
		_currentResetTime = 0.0f;
		_resetTime = 0.0f;

		//파티클 초기화
		_preparePS = NULL;
		_actionPS = NULL;
		_finishPS = NULL;

		_SkillRenderType = SR_One;

	};
	~dxSkill() {};
};

