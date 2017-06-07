#pragma once
#include "gameNode.h"

class keyFrameAniTestScene : public gameNode
{
public:
	//�ִϸ��̼� Ű������ ����ü
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
	LPDIRECT3DVERTEXBUFFER9 _vb;			//��������
	LPDIRECT3DINDEXBUFFER9  _ib;			//�ε�������

	MAP_TRANS				_boneMap;		//����
	MAP_TRANS				_meshMap;		//��
	transform				_trans;		

	camera					_mainCamera;	//����ī�޶�

	float					_nowFrame;		//����������
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

