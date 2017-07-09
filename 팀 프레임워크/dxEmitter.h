#pragma once
#include "dxParticle.h"
#include "dxModule.h"
#include "dxModuleKit.h"

enum EMITTER_TYPE
{
	ET_POINT,
	ET_PLANE,
	ET_BOARD,
	ET_MESH
};
#define ET_POINT	ET_POINT
#define ET_PLANE	ET_PLANE
#define ET_BOARD	ET_BOARD
#define ET_MESH		ET_MESH

class dxEmitter
{
protected:
	//��ƼŬ �Ӽ���
	//list<tagDxAttribute> _ptcList;
	vector<tagDxAttribute> _ptcList;
	dxModuleKit* _module;

	//��ƼŬ Ÿ��
	EMITTER_TYPE _EmitterType;

	//��ƼŬ �ý��ۿ� Ʈ������
	dx::transform* _psTrans;

	dx::transform* _psBoardTrans;	//�������

	dx::transform* _trans;

	LPDIRECT3DTEXTURE9	_texture;			//�ؽ���

	float _constPaticleSize;

	//�̹��� ����(�ð� �����)
	int _emitterNum;

	bool _realtimeTrackingPosOn;

protected:
	//��ü ȸ����
	D3DXVECTOR3 _allRotate;

	D3DXVECTOR3 _allRotateSpeed;

protected:
	//��ƼŬ ���� �� �ð� ����
	int		_onePtcNum;					//������ ������ �ѹ��� �վ�� ��ƼŬ ����
	DWORD	_totalPtcNum;				//�� ��ƼŬ ����

	float	_spawnTime;					//����
	float	_spawnCurrentTime;			//����Ÿ��

	int		_drawPtcNum;				//�׸� ��ƼŬ ����	



	bool _InitActiveStop;
	bool _initActiveTimeOn;

	float _initActiveLimitTime;
	float _initActiveCurrentTime;

protected:
	//Ȱ���ð� ����
	bool	_activeTimeCheckOn;
	float	_activeCurrentTime;
	float	_activeLimitTime;

	bool	_activeRenderControlOn;
	bool	_activeRenderOn;

	//���۽ð� ����
	bool	_startTimeCheckOn;
	float	_startLimitTime;			//ó�� ���� �Ѱ� �ð�
	float	_startCurrentTime;			//ó�� ���� ����ð�

	bool	_startRenderOn;

protected:
	//�̸� ������Ʈ �κ� ����
	int _preInitPtcCurrentNum;
	int _oneFramePtcCurrentNum;
	int _oneFramePtcNum;

	//�����ð� ����
	float _accrueTime;
	float _preLimitTime;

	bool _preUpdateOn;
	bool _preOneSettingOn;
protected:
	//������ ����
	bool _billBoardY_On;

public:		//�Լ�

	//���� �����Լ�
	//virtual HRESULT init(string textureFileName, int particleNumber) = 0;
	virtual HRESULT init(string, int OneTimePaticleNum, float spawnTime, int totalParticlenum) = 0;
	virtual void preUpdate();	//��ȹ�� â�������� �ᱹ �����ߴ�.
	virtual void update() = 0;
	virtual void render() = 0;
	//virtual void reset() = 0;

public:	//����
	virtual void release();
	//virtual void CopyInit() = 0;

public:
	dxModuleKit* Module(void) { return _module; };
	dx::transform*	Transform() { return _trans; }

public: //=======================================================================================================================
	//ȸ�� ��������
	void InitAllStartRotate(float startX, float startY, float startZ) { _allRotate = D3DXVECTOR3(startX, startY, startZ); };

	//ȸ�� ���ǵ�
	void InitAllRotateSpeed(float speedX, float speedY, float speedZ) { _allRotateSpeed = D3DXVECTOR3(speedX, speedY, speedZ); };


public: //=======================================================================================================================
	//��ġ Ÿ�� ����
	void SetPositionType(PTC_POSITION_TYPE posType = PTC_SPHERE) { _module->SetPositionType(posType); }
	void InitRandomPosSphereRadius(float min, float max) { _module->InitRandomPosSphereRadius(min, max); }

	//�� ����
	void InitDirSphere(float dirX, float dirY, float dirZ) { _module->InitDirSphere(dirX, dirY, dirZ); }

	//��ġ
	void InitRandomPositionX(float min, float max) { _module->InitRandomPositionX(min, max); }
	void InitRandomPositionY(float min, float max) { _module->InitRandomPositionY(min, max); }
	void InitRandomPositionZ(float min, float max) { _module->InitRandomPositionZ(min, max); }


public: //=======================================================================================================================
	//��ġ���� ����
	void InitRandomPosExplosionVel(float min, float max) { _module->InitRandomPosExplosionVel(min, max); }

	//��ġ���� ���� �׷���
	void addPosExplosionVelGraph(float point, float min, float max) { _module->addPosExplosionVelGraph(point, min, max); }


public:	//=======================================================================================================================
	//��ġ �߽� ȸ��
	void InitRandomPosRotAngleSpeedX(float min, float max) { _module->InitRandomPosRotAngleSpeedX(min, max); }
	void InitRandomPosRotAngleSpeedY(float min, float max) { _module->InitRandomPosRotAngleSpeedY(min, max); }
	void InitRandomPosRotAngleSpeedZ(float min, float max) { _module->InitRandomPosRotAngleSpeedZ(min, max); }


public:	//=======================================================================================================================
	//���� ����
	void InitConstAttractCenter(float x, float y, float z) { _module->InitConstAttractCenter(x, y, z); }
	//���� ����
	void InitAttractCenterX(float min, float max) { _module->InitAttractCenterX(min, max); }
	void InitAttractCenterY(float min, float max) { _module->InitAttractCenterY(min, max); }
	void InitAttractCenterZ(float min, float max) { _module->InitAttractCenterZ(min, max); }


public:  //=======================================================================================================================
	 //�ӵ�
	void InitRandomVelocityX(float min, float max) { _module->InitRandomVelocityX(min, max); }
	void InitRandomVelocityY(float min, float max) { _module->InitRandomVelocityY(min, max); }
	void InitRandomVelocityZ(float min, float max) { _module->InitRandomVelocityZ(min, max); }

	//�ӵ� �׷���
	void addVelocityGraphX(float point, float min, float max) { _module->addVelocityGraphX(point, min, max); }
	void addVelocityGraphY(float point, float min, float max) { _module->addVelocityGraphY(point, min, max); }
	void addVelocityGraphZ(float point, float min, float max) { _module->addVelocityGraphZ(point, min, max); }

public:  //=======================================================================================================================
		//���ӵ�
	void InitRandomAccelerationX(float min, float max) { _module->InitRandomAccelerationX(min, max); }
	void InitRandomAccelerationY(float min, float max) { _module->InitRandomAccelerationY(min, max); }
	void InitRandomAccelerationZ(float min, float max) { _module->InitRandomAccelerationZ(min, max); }

	//���ӵ� �׷���
	void addAccelGraphX(float point, float min, float max) { _module->addAccelGraphX(point, min, max); }
	void addAccelGraphY(float point, float min, float max) { _module->addAccelGraphY(point, min, max); }
	void addAccelGraphZ(float point, float min, float max) { _module->addAccelGraphZ(point, min, max); }

public:  //=======================================================================================================================
		 //��
	void InitRandomColorR(float min, float max) { _module->InitRandomColorR(min, max); }
	void InitRandomColorG(float min, float max) { _module->InitRandomColorG(min, max); }
	void InitRandomColorB(float min, float max) { _module->InitRandomColorB(min, max); }

	//�� �Ҹ�
	void InitRandomColorFadeR(float min, float max) { _module->InitRandomColorFadeR(min, max); }
	void InitRandomColorFadeG(float min, float max) { _module->InitRandomColorFadeG(min, max); }
	void InitRandomColorFadeB(float min, float max) { _module->InitRandomColorFadeB(min, max); }

	//����
	void InitRandomAlpha(float min, float max) { _module->InitRandomAlpha(min, max); }
	void InitRandomAlphaFade(float min, float max) { _module->InitRandomAlphaFade(min, max); }

	//���� �׷���
	void addAlphaGraph(float point, float min, float max) { _module->addAlphaGraph(point, min, max); };

public:
	//����
	void InitRandomLifeTime(float min, float max) { _module->InitRandomLiftTime(min, max); }

public:	//=======================================================================================================================
		//������ ����
	void InitRandomSize(float min, float max) { _module->InitRandomSize(min, max); }
	void InitRandomSizeEnd(float min, float max) { _module->InitRandomSizeEnd(min, max); }

	//������ �׷��� ����
	void InitConstSize(float size) { _constPaticleSize = size; }

	void addSizeGraph(float point, float min, float max) { _module->addSizeGraph(point, min, max); };


public:	//=======================================================================================================================

	//�� ȸ�� ������ �ʱ�ȭ
	void InitCircleRadiusX(float min, float max) { _module->InitCircleRadiusX(min, max); }
	void InitCircleRadiusY(float min, float max) { _module->InitCircleRadiusY(min, max); }
	void InitCircleRadiusZ(float min, float max) { _module->InitCircleRadiusZ(min, max); }
	//�� ȸ�� ���ǵ�
	void InitCircleAngleSpeedX(float min, float max) { _module->InitCircleAngleSpeedX(min, max); }
	void InitCircleAngleSpeedY(float min, float max) { _module->InitCircleAngleSpeedY(min, max); }
	void InitCircleAngleSpeedZ(float min, float max) { _module->InitCircleAngleSpeedZ(min, max); }
	//�� ȸ�� ���۰���								  
	void InitCircleStartAngleX(float min, float max) { _module->InitCircleStartAngleX(min, max); }
	void InitCircleStartAngleY(float min, float max) { _module->InitCircleStartAngleY(min, max); }
	void InitCircleStartAngleZ(float min, float max) { _module->InitCircleStartAngleZ(min, max); }
	//��ȸ�� ������ ������
	void InitCircleRadiusEndX(float min, float max) { _module->InitCircleRadiusEndX(min, max); }
	void InitCircleRadiusEndY(float min, float max) { _module->InitCircleRadiusEndY(min, max); }
	void InitCircleRadiusEndZ(float min, float max) { _module->InitCircleRadiusEndZ(min, max); }


public:	//=======================================================================================================================
	//ȸ������ ����
	void InitRotateStartAngleX(float min, float max) { _module->InitRotateStartAngleX(min, max); }
	void InitRotateStartAngleY(float min, float max) { _module->InitRotateStartAngleY(min, max); }
	void InitRotateStartAngleZ(float min, float max) { _module->InitRotateStartAngleZ(min, max); }

	//ȸ������ ���ǵ�
	void InitRotateAngleSpeedX(float min, float max) { _module->InitRotateAngleSpeedX(min, max); }
	void InitRotateAngleSpeedY(float min, float max) { _module->InitRotateAngleSpeedY(min, max); }
	void InitRotateAngleSpeedZ(float min, float max) { _module->InitRotateAngleSpeedZ(min, max); }

public:	//=======================================================================================================================
	//���μ���
	void InitConstHV(float horizontal, float vertical) { _module->InitConstHV(horizontal, vertical); }

	//�� �󿡼� �߽� ��ġ�� ����
	void InitCenterPointHV(float pointH, float pointV) { _module->InitCenterPointHV(pointH, pointV); }

public:	//=======================================================================================================================
	//UV�ִϸ��̼�
	void InitAnimation(int inFrameMaxX, int inFrameMaxY, int inTotalFrame = 0) { _module->InitAnimation(inFrameMaxX, inFrameMaxY, inTotalFrame); }

	//�ִϸ��̼� �����
	void InitConstAniReactivateNum(int inReactiveateNum) { _module->InitConstAniReactivateNum(inReactiveateNum); }

	//�ִϸ��̼� ���������� ������ ��������
	void InitAniPlaySection(int inStartFrameNum, int inEndFrameNum) { _module->InitAniPlaySection(inStartFrameNum, inEndFrameNum); }

	//UV�̹��� ����
	void uvReverseImgU() { _module->uvReverseImgU(); }
	void uvReverseImgV() { _module->uvReverseImgV(); }

	//void InitRandomSpawnTime(float min, float max) { init(_textureFileName, _onePtcNum, RandomFloatRange(min, max)); }
	//void InitRandomDirectionVelocity(float min, float max) { _module->InitRandomDirectionVelocity(min, max); }
public:
	//�ǽð� ��������
	void setRealtimeTrackingPosOn() { _realtimeTrackingPosOn = true; }
	bool getRealtimeTrackingPosOn() { return _realtimeTrackingPosOn; }

public:
	//Ư���Լ�
	DWORD FtoDw(float f) { return *((DWORD*)&f); }
	//Ÿ���Լ�
	EMITTER_TYPE GetType(void) { return this->_EmitterType; };

public:
	//����
	void reset()
	{
		_activeRenderOn = true;
		_activeRenderControlOn = true;

		_InitActiveStop = FALSE;
		_initActiveCurrentTime = 0.0f;


		_ptcList.clear();
		_ptcList.resize(_totalPtcNum);
		_activeCurrentTime = 0.0f;
		_spawnCurrentTime = _spawnTime;
		_startCurrentTime = 0.0f;
		_activeCurrentTime = 0.0f;

		if (_startTimeCheckOn) { _startRenderOn = FALSE; }

	}
public:
	//�۵� �ð� ����
	void SetActiveLimitTime(float inTime, bool inRenderControlOn = true)
	{
		_activeLimitTime = inTime;
		_activeRenderControlOn = inRenderControlOn;
		_activeCurrentTime = 0.0f;
		_activeTimeCheckOn = TRUE;
	};

	void SetStartLimitTime(float inTime)
	{
		_startLimitTime = inTime;
		_startCurrentTime = 0.0f;
		_startTimeCheckOn = TRUE;
		_startRenderOn = FALSE;
	}

	//�׷��̽������� ���ķ�
	void setGrayScaleAlphaOn(void);

	bool autoActiveTimeCheck(float timeDelta);

	bool autoStartTimeCheck(float timeDelta);

	void setParticleSystemTrans(dx::transform* inTrance) { _psTrans = inTrance; }

	void setPsBoardTrans(dx::transform* inBoardTrance) { _psBoardTrans = inBoardTrance; }

	void setEmitterNum(int num) { _emitterNum = num; };

	void setInitActiveLimitTime(float inTime) { _initActiveLimitTime = inTime; _initActiveTimeOn = TRUE; };

public:
	void EmitterInit(void)
	{
		//��� �ʱ�ȭ
		_module = new dxModuleKit;
		_trans = new dx::transform;

		//Ʈ���� �ʱ�ȭ
		_psTrans = NULL;
		_psBoardTrans = NULL;
		_module->init();

		//�۵��ð� �ʱ�ȭ
		_activeTimeCheckOn = FALSE;
		_activeCurrentTime = 0.0f;
		_activeLimitTime = 0.0f;

		_activeRenderOn = true;
		_activeRenderControlOn = true;

		//���۽ð� �ʱ�ȭ
		_startTimeCheckOn = FALSE;
		_startLimitTime = 0.0f;
		_startCurrentTime = 0.0f;

		_startRenderOn = true;

		//�̹��� ����
		_emitterNum = 1;


		_psTrans = NULL;

		_allRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_allRotateSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�̸� ������Ʈ �ʱ�ȭ
		_preInitPtcCurrentNum = 0;
		_oneFramePtcCurrentNum = 0;
		_oneFramePtcNum = 0;

		_accrueTime = 0.0f;
		_preLimitTime = 0.0f;

		_preUpdateOn = true;
		_preOneSettingOn = true;

		_realtimeTrackingPosOn = false;

		_InitActiveStop = FALSE;

		_initActiveTimeOn = FALSE;

		_initActiveLimitTime = 0.0f;
		_initActiveCurrentTime = 0.0f;


		_billBoardY_On = FALSE;

	}
	dxEmitter() {};
	~dxEmitter() {};



};

