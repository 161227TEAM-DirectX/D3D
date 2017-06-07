#pragma once
#include "gameNode.h"

class aniTestScene : public gameNode
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

private:
	LPDIRECT3DVERTEXBUFFER9 _vb;			//��������
	LPDIRECT3DINDEXBUFFER9  _ib;			//�ε�������
	transform				_target;		//Ÿ��
	MAP_TRANS				_boneMap;		//����
	MAP_TRANS				_meshMap;		//��
	camera					_mainCamera;	//����ī�޶�

	float					_nowFrame;
	vector<LPKEY_FRAME>		_rightHipKeyFrames;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateCube();
	void RenderCube();

	aniTestScene() {}
	~aniTestScene() {}
};

