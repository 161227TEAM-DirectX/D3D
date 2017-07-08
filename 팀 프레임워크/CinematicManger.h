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
	int ECount;
	float time;

	float cameraPositionX, cameraPositionY, cameraPositionZ;

	D3DXVECTOR3 lookPos;

	CINEMA texture;

private:
	vector<tagSaveCinematic> vcinematic;
	tagSaveCinematic         cinematic;
	vector<tagSaveCinematic> vCTemp;
	tagSaveCinematic Ctemp;

	vector<tagSaveEndingCinematic> Ecinematic;
	tagSaveEndingCinematic         Einematic;
	vector<tagSaveEndingCinematic> ECTemp;
	tagSaveEndingCinematic         Etemp;

	SYNTHESIZE(int, number, GSnumber);
public:
	void init();

	void cinematicInit();
	void cinematicLoad(D3DXVECTOR3* position, camera* camera, dx::transform* transform);
	void cinematicSave(D3DXVECTOR3* position, camera* camera);

	void cinematicEInit();
	void cinematicEndingLoad(camera * _camera);
	void cinematicEndingSave(camera * _camera);

	void cinemaRender(camera* camera);


	CinematicManger() {}
	~CinematicManger() {}
};