#pragma once
#include "dxParticleSystem.h"

class dxSkillContainer
{
protected:
	enum SKILL_RENDER_TYPE
	{
		SR_One,
		SR_Array,
		SR_Big,
		SR_Custom
	};
//
//#define SR_One		SR_One
//#define	SR_Array	SR_Array
//#define	SR_Big		SR_Big
//#define SR_Custom	SR_Custom

	//dxSkillFunction _skillFunc;

protected:
	//렌더 타입 선언부
	SKILL_RENDER_TYPE _SkillRenderType;

	//클래스 번호
	int _skillNumber;
	string _className;

	//스킬
	float _castTime;

	

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

	//파티클 시스템 벡터0
	vector<dxParticleSystem*> _vPrepaerPS;
	vector<dxParticleSystem*> _vActionPS;
	vector<dxParticleSystem*> _vFinishPS;

	//파티클 시스템 벡터0
	vector<dxParticleSystem*>* _pvPrepaerPS;
	vector<dxParticleSystem*>* _pvActionPS;
	vector<dxParticleSystem*>* _pvFinishPS;

	int _pvPrepaerMaxNum;
	int _pvActionMaxNum;
	int _pvFinishMaxNum;

	//파티클 시스템 배열
	/*dxParticleSystem* _arrayPreparePS;
	dxParticleSystem* _arrayActionPS;
	dxParticleSystem* _arrayFinishPS;*/

	//파티클 시스템 배열개수
	//int _pvPrepareSize;
	//int _pvActionSize;
	//int _pvFinishSize;

	boundSphere* _actionSphereCollision;
	boundSphere* _targetSphereCollision;

	//마지막 시간
	float _resetTime;
	float _currentResetTime;
	
	//디폴트 렌더 여부
	//bool _defualtRendrOn;

	bool _endOn;

	dx::transform* _actionTrans;
	dx::transform* _targetTrans;

public:
	virtual HRESULT init();
	virtual void release();
	//virtual void update(transform* playerTrans, transform* tagetTrans) = 0;
	//virtual void update(transform* playerTrans, transform* tagetTrans);
	void update();	//NO버츄얼....부모가 업데이트함.
	void render();

public:
	//동작 시작
	void Start()
	{
		if (_skillStartOn == FALSE) { _skillPrepareOn = true; };
		_skillStartOn = true; 
		_endOn = false;
	}

	virtual bool getEnd(void)
	{
		if (_skillStartOn)
		{
			if (_endOn)
			{
				_endOn = true;
				return true;
			}
		}

		return false;
	}

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
	//virtual void setPlayer(dx::transform* inPlayerTrans) { _playerTrans = inPlayerTrans; };
	virtual void setTarget(dx::transform* inTargetTrans) { _targetTrans = inTargetTrans; };
	//virtual void setAction(transform* inTargetTrans) { _actionTrans = inTargetTrans; };

public:
	virtual void ReleaseSkillPS();

public:
	//일반
	void setPreparePS(string psName) { PSM->initPS(_preparePS, psName); }
	void setActionPS(string psName)  { PSM->initPS(_actionPS, psName); }
	void setFinishPS(string psName)  { PSM->initPS(_finishPS, psName); }

public:
	//벡터용
	void setArrayPreparePS(string psName, int arrayNum) { PSM->initArrayPS(_vPrepaerPS, arrayNum, psName); }
	void setArrayActionPS(string psName, int arrayNum) { PSM->initArrayPS(_vActionPS, arrayNum, psName); }
	void setArrayFinishPS(string psName, int arrayNum) { PSM->initArrayPS(_vFinishPS, arrayNum, psName); }

	

public:
	//포인터형 벡터용
	void setMaxNumPreparePS(int MaxNum) { _pvPrepaerPS = new vector<dxParticleSystem*>[MaxNum]; _pvPrepaerMaxNum = MaxNum; }
	void setMaxNumActionPS(int MaxNum) { _pvActionPS = new vector<dxParticleSystem*>[MaxNum]; _pvActionMaxNum= MaxNum; }
	void setMaxNumFinishPS(int MaxNum) { _pvFinishPS = new vector<dxParticleSystem*>[MaxNum]; _pvFinishMaxNum = MaxNum; }

	void setPvPreparePS(int skillNum,string psName, int arrayNum) { PSM->initArrayPS(_pvPrepaerPS[skillNum], arrayNum, psName); }
	void setPvActionPS(int skillNum, string psName, int arrayNum) { PSM->initArrayPS(_pvActionPS[skillNum], arrayNum, psName); }
	void setPvFinishPS(int skillNum, string psName, int arrayNum) { PSM->initArrayPS(_pvFinishPS[skillNum], arrayNum, psName); }

public:
	bool getActive() { return _skillStartOn; }
	//bool get

	

protected:
	bool AutoResetTime(float inTime);
	

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




protected:
	void ContainerInit(void)
	{
		//동작들 초기화
		_skillStartOn = false;
		_skillFinshOn = false;
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

		_endOn = true;
	}

	public:
	//생성자
	dxSkillContainer() {};
	~dxSkillContainer() {};
};

