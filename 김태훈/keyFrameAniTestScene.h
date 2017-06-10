#pragma once
#include "gameNode.h"

class keyFrameAniTestScene : public gameNode
{
public:
	//애니메이션 키프레임 구조체
	typedef struct tagKeyFrame
	{
		int frame;
		transform trans;

		tagKeyFrame() : frame(0) {}
		tagKeyFrame(int frame, transform& other)
		{
			this->frame = frame;
			this->trans = other;
		}
	}KEY_FRAME, *LPKEY_FRAME;

private:
	typedef map<string, transform*> MAP_TRANS;
	typedef MAP_TRANS::iterator		MAP_TRANS_ITER;

	typedef vector<LPKEY_FRAME>		KEY_FRAMES;
	typedef map<string, KEY_FRAMES>	MAP_BONE_KEYFRAMES;

private:
	LPDIRECT3DVERTEXBUFFER9 _vb;			//정점버퍼
	LPDIRECT3DINDEXBUFFER9  _ib;			//인덱스버퍼

	MAP_TRANS				_boneMap;		//뼈대
	MAP_TRANS				_meshMap;		//살
	transform				_trans;		

	camera					_mainCamera;	//메인카메라

	float					_nowFrame;		//현재프레임
	MAP_BONE_KEYFRAMES		_animationFrames;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateCube();
	void RenderCube();

	keyFrameAniTestScene() {}
	~keyFrameAniTestScene() {}
};

