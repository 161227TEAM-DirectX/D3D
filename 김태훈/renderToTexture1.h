#pragma once
#include "gameNode.h"

#define OBJECT_NUM 10

class renderToTexture1 : public gameNode
{
private:
	vector<light*>			_lights;			//����
	vector<baseObject*>		_renderObjects;		//���� ��ġ�� ���� ������Ʈ �迭
	vector<baseObject*>		_cullObjects;		//�ø��� ������Ʈ
	camera*					_extraCam;			//�߰� ī�޶�

	LPDIRECT3DTEXTURE9		_renderTexture;		//�������� Texture
	LPDIRECT3DSURFACE9		_renderSurface;		//����  Texture Depth ���ۿ� Stencil ���۰� �ִ� Surface

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void renderSprite(void);

	renderToTexture1() {}
	~renderToTexture1() {}
};

