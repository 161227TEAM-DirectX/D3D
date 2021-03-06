#pragma once
#include "xMeshSkinned.h"

class skinnedAnimation
{
private:
	typedef map<BONE*, dx::transform*>				MAP_BONETRANSFORM;	//매핑되는 본Transform 맵
	typedef map<string, LPD3DXANIMATIONSET >	MAP_ANIMSET;
	typedef vector< LPD3DXANIMATIONSET >		VEC_ANIMSET;

private:
	xMeshSkinned*		_pSkinnedMesh;
	MAP_BONETRANSFORM	_mapApplyBoneTransform;
	MAP_BONETRANSFORM	_mapBoneTransform;

	/////////////////////////////////////////////////////////////////////////////////

	LPD3DXANIMATIONCONTROLLER	_pAnimController;			//Animation 컨트롤러
	UINT						_AnimNum;					//Animation 갯수
	MAP_ANIMSET					_mapAnimSet;				//Map 으로 되어있는 AnimationSet
	VEC_ANIMSET					_vecAnimSet;				//Vector 로 되어있는 AnimationSet
	LPD3DXANIMATIONSET			_pNowPlayAnimationSet;		//현제 플레이되고있는 AnimationSet
	D3DXTRACK_DESC				_Track_Desc_0;				//0번 Track_Desc ( 0 번 Track 의 정보 )
	bool						_bPlay;						//지금 플레이 중이니?
	bool						_bLoop;						//루프 플레이니?
	LPD3DXANIMATIONSET			_pPrevPlayAnimationSet;		//OneShot 플레이시 한번 Animation 플레이되고 다시 되돌아갈 Animaiton
	float						_fCrossFadeTime;			//크로스페이드 타임
	float						_fLeftCrossFadeTime;		//남은크로스페이드 타임
	float						_fOutCrossFadeTime;			//OneShot Animation 끝나고 되돌아갈때 CrossFade 타임
	double						_AnimationPlayFactor;		//Animation 진행 Factor ( 0 이면 처음 1 일수록 마지막 )
	float						_fAnimDelta;
	float						_AnimSpeed;
	string						_AnimName;					//현재 실행하고자 하는 애니메이션

public:
	HRESULT	init(xMeshSkinned* pSkinnedMesh);
	void release();
	void update();
	void updateBone();
	void render(dx::transform* _transform);
	void renderBoneName(camera* pCam, dx::transform* _transform);

	void Play(string animName, float crossFadeTime = 0.0);
	void Play(int animIndex, float crossFadeTime = 0.0);
	void Play(LPD3DXANIMATIONSET animSet, float crossFadeTime = 0.0);
	void PlayOneShot(string animName, float inCrossFadeTime = 0.0, float outCrossFadeTime = 0.0f);
	void PlayOneShotAfterHold(string animName, float crossFadeTime = 0.0);
	void Stop() { _bPlay = false; }
	void SetPlaySpeed(float speed);

	//void setAnimTrack() { _pAnimController->GetTrackDesc(0, &_Track_Desc_0); }

	D3DXTRACK_DESC getTrackDesc0() { return _Track_Desc_0; }
	void setTrackDesc0(D3DXTRACK_DESC DESC0) { _pAnimController->SetTrackDesc(0, &DESC0); }

	LPD3DXANIMATIONSET getNowPlayAnimSet() { return _pNowPlayAnimationSet; }

	void AddBoneTransform(std::string boneName, dx::transform* _transform);
	void AddApplyTransform(std::string boneName, dx::transform* _transform);
	void RemoveBoneTransform(std::string boneName);
	void RemoveApplyTransform(std::string boneName);

	double& getAnimationPlayFactor(void) { return _AnimationPlayFactor; }
	LPD3DXANIMATIONSET& getAnimationSet(void) { return _pNowPlayAnimationSet; }

	LPD3DXANIMATIONCONTROLLER getAnimContorller(void) { return _pAnimController; }


	xMeshSkinned* getSkinnedMesh() { return _pSkinnedMesh; }
	//LPD3DXANIMATIONSET getNowPlayanim() { return _pNowPlayAnimationSet; }
	float getAnimFactor() { return _AnimationPlayFactor; }

public:
	skinnedAnimation();
	~skinnedAnimation();

private:
	//Animation 을 바꾼다.
	void SetAnimation(LPD3DXANIMATIONSET animSet);
};

