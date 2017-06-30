#pragma once
#include "iGameNode.h"

struct RGBSTRUCT
{
	bool start;
	float a;
	float r;
	float g;
	float b;
	bool rBool;
	bool gBool;
	bool bBool;
	bool aBool;
};

struct DoorVertex
{
	D3DXVECTOR3 xyz;
	DWORD color;

	enum FVF
	{
		FVF_Flags = D3DFVF_XYZ | D3DFVF_DIFFUSE
	};
};

struct DoorShader
{
	bool							AlphaLayer;
	bool							_using;

	D3DXVECTOR2						textureScale;
	float							waveFreq;
	float							waveAmp;

	float							BumpScale;
	D3DXVECTOR2						bumpSpeed;
	D3DXVECTOR4						deepColor;
	D3DXVECTOR4						shallowColor;
	float							waterAmount;

	D3DXVECTOR4						reflectionColor;
	float							reflectionAmount;
	float							reflectionBlur;

	float							fresnelPower;
	float							fresnelBias;
	float							hdrMultiplier;


};

class Tportal
{
private:
	camera* _camera;
	dx::transform*					_trans;
private:
	LPDIRECT3DVERTEXBUFFER9 _doorVertexBuffer;
	LPDIRECT3DTEXTURE9				_doorBump;
	LPDIRECT3DCUBETEXTURE9			_doorCube;;
	LPD3DXEFFECT					_doorEffect;
	D3DXVECTOR4						_eye;

	DoorShader _doorShader;
	DoorVertex _doorVertex[6];

	RGBSTRUCT _rgb;
	float _doorTime;

public:

	HRESULT init();
	void release();
	void render();

	void portalSet(dx::transform * inTrans);
	void update();
	void renderPortal();

	void LinkCamera(camera& cc) { this->_camera = &cc; }

	Tportal() {}
	~Tportal() {}
};