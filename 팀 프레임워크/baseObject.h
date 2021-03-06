#pragma once

class baseObject
{
public:
	xMesh*				_mesh;					//내가 사용할 메쉬
	dx::transform*		_transform;				//트렌스폼
	boundBox			_boundBox;				//충돌박스
	bool				_ignoreCreateShadow;	//쉐도우맵 만들때 무시되냐?
	skinnedAnimation*	_skinnedAnim;			//스킨드 애니메이션

protected:
	bool				_isActive;				//활성화 여부
	int					_objectNumber;
	int                 _portalNumber;
	float				_objectRatation;

protected:
	//override로 필요하면 재정의 해서 사용하기
	virtual void baseObjectEnable() {}			//BaseObject가 활성화 될때 실행
	virtual void baseObjectDisable() {}			//BaseObject가 비활성화 될때 실행
	virtual void baseObjectUpdate() {}			//BaseObject가 Update 때 실행
	virtual void baseObjectNoActiveUpdate() {}	//BaseObject가 비활성화시 업데이트 실행
	virtual void baseObjectRender();			//BaseObject를 그릴때 실행

public:
	void update();
	void render();

	//렌더링 될 메쉬를 세팅한다.
	void setMesh(xMesh*	pMesh);
	//활성화 세팅
	void setActive(bool isActive);
	//활성화 여부를 얻는다.
	bool getActive() { return _isActive; }

	skinnedAnimation& getSkinnedAnim(void) { return *_skinnedAnim; }

	//세팅된 메쉬에 따라 바운드박스를 재계산 한다.
	void computeBoundBox();

	//바운딩박스이 밑바닥Y값을 넘기기위해 get만듬
	boundBox getBoundBox(void) { return _boundBox; }

	//오브젝트 로테이트 , 넘버
	int getportalNumber(void) { return _portalNumber; }
	int getObjectNumber(void) { return _objectNumber; }
	float getObjectRotation(void) { return _objectRatation; }

	void SetportalNumber(int portalNumber) { _portalNumber = portalNumber; }
	void SetObjectNumber(int ObjectNumber) { _objectNumber = ObjectNumber; }
	void SetObjectRotation(float ObjectRotation) { _objectRatation = ObjectRotation; }


	baseObject();
	virtual ~baseObject();
};

