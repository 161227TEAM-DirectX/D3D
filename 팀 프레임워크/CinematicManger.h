#pragma once
#include "singletonBase.h"

struct CINEMA
{
	LPDIRECT3DTEXTURE9 tex;
	RECT rc1, rc2;
};

class CinematicManger : public singletonBase <CinematicManger>
{
private:
	float RotateAngle;
	float RotateRadian;

	float cameraY;
	float cameraXZ;

	D3DXVECTOR3 cameraHeight;

	int iCount;
	float time;

	float cameraPositionX, cameraPositionY, cameraPositionZ;

	D3DXVECTOR3 lookPos;

	CINEMA texture;


public:
	void cinematicInit(bool save);
	void cinematicLoad(D3DXVECTOR3* position, camera* camera, dx::transform* transform);
	void cinematicSave(D3DXVECTOR3* position, camera* camera);
	void cinemaRender(camera* camera);


	CinematicManger() {}
	~CinematicManger() {}
};