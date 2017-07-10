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

	CINEMA endingTexure;
	CINEMA scene4Texure;

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
	SYNTHESIZE(bool, cineMticE4Bool, GScineMticE4Bool);
	SYNTHESIZE(bool, cineMticBossBool, GScineMticBossBool);

public:
	void init();

	void cinematicBossInit();
	void cinematicBossLoad(D3DXVECTOR3* position, camera* camera, dx::transform* transform);
	void cinematicBossSave(D3DXVECTOR3* position, camera* camera);
	void cinematicBossRender();

	void cinematicE4Init();
	void cinematicE4Load(camera * _camera , bool cinematic);
	void cinematicE4Save(camera * _camera);
	void cinematicE4Render(camera* camera);

	void cinematicEndingInit();
	void cinematicEndingLoad(camera * _camera);
	void cinematicEndingSave(camera * _camera);
	void cinematicEndingRender();


	CinematicManger() {}
	~CinematicManger() {}
};