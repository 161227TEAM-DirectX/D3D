#include "stdafx.h"
#include "CinematicManger.h"


void CinematicManger::init()
{
	cameraHeight = { 0, -5.0f, 0 };
	RotateAngle = 0.0f;
	RotateRadian = D3DXToRadian(15.0f);

	cameraY = 2.0f;
	cameraXZ = 5.0f;
	iCount = 0;
	ECount = 0;
	time = 0;

	cineMticE4Bool = false;
	cineMticBossBool = false;
	
	vcinematic.clear();
}

void CinematicManger::cinematicSwordInit()
{
	IOCINEMATICMANAGER->loadFile("검2");

	for (int i = 0; i < IOCINEMATICMANAGER->getCount(); i++)
	{
		cinematic = IOCINEMATICMANAGER->findTag("카메라" + to_string(i));
		vcinematic.push_back(cinematic);
	}
}

void CinematicManger::cinematicBossInit()
{
	IOCINEMATICMANAGER->loadFile("보스시네마틱");

	for (int i = 0; i < IOCINEMATICMANAGER->getCount(); i++)
	{
		cinematic = IOCINEMATICMANAGER->findTag("카메라" + to_string(i));

		vcinematic.push_back(cinematic);
	}
}

void CinematicManger::cinematicBossLoad(D3DXVECTOR3 * position, camera * camera, dx::transform * transform)
{
	if (cineMticBossBool == false)
	{
		if (iCount < vcinematic.size())
		{
			lookPos = *position;

			D3DXVECTOR3 temp = { vcinematic[iCount].X, vcinematic[iCount].Y, vcinematic[iCount].Z };

			D3DXVec3TransformCoord(&temp, &temp, &transform->GetWorldRotateMatrix());

			camera->LookPosition((lookPos + D3DXVECTOR3(0, vcinematic[iCount].Height, 0)));
			camera->SetWorldPosition(position->x + temp.x, position->y + temp.y, position->z + temp.z);

			iCount++;

			camera->updateMatrix();
			camera->updateCamToDevice();
			camera->updateFrustum();
		}
		else
		{
			cineMticBossBool = true;
		}
	}
}

void CinematicManger::cinematicBossSave(D3DXVECTOR3 * position, camera * camera)
{
	lookPos = *position;

	RotateAngle += RotateRadian *_timeDelta;

	cameraPositionX = lookPos.x + cos(RotateAngle)* cameraXZ;
	cameraPositionY = lookPos.y + cameraY;
	cameraPositionZ = lookPos.z + sin(RotateAngle)*cameraXZ;

	camera->LookPosition(lookPos + cameraHeight);
	camera->SetWorldPosition(cameraPositionX, cameraPositionY, cameraPositionZ);

	camera->updateMatrix();
	camera->updateCamToDevice();
	camera->updateFrustum();

	//위로 올라가는거
	if (KEYMANAGER->isStayKeyDown('Y'))
	{
		cameraHeight.y += 2.0f;
		cameraY += 2.0f;
	}
	//아래로 내려가는거
	if (KEYMANAGER->isStayKeyDown('U'))
	{
		cameraHeight.y -= 2.0f;
		cameraY -= 2.0f;
	}
	//각도를 위로올리는거
	if (KEYMANAGER->isStayKeyDown('H'))
	{
		cameraHeight.y += 2.0f;
	}
	//각도를 아래로내리는거
	if (KEYMANAGER->isStayKeyDown('J'))
	{
		cameraHeight.y -= 2.0f;
	}

	//캠확대 , 축소
	if (KEYMANAGER->isStayKeyDown('I')) 	cameraXZ += 0.5f;
	if (KEYMANAGER->isStayKeyDown('O')) 	cameraXZ -= 0.5f;

	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		if (RotateRadian >= D3DXToRadian(15))
		{
			RotateRadian = D3DXToRadian(40);
		}
		else
		{
			RotateRadian += D3DXToRadian(1);
		}
	}

	if (KEYMANAGER->isStayKeyDown('X'))
	{
		if (RotateRadian <= D3DXToRadian(0))
		{
			RotateRadian = D3DXToRadian(0);
		}
		else
		{
			RotateRadian -= D3DXToRadian(1);
		}
	}

	if (KEYMANAGER->isToggleKey('M'))
	{
		Ctemp.infoName = "카메라" + to_string(iCount);
		Ctemp.X = camera->getCameraPos().x - lookPos.x;
		Ctemp.Y = camera->getCameraPos().y - lookPos.y;
		Ctemp.Z = camera->getCameraPos().z - lookPos.z;
		Ctemp.Height = cameraHeight.y;

		vCTemp.push_back(Ctemp);

		iCount++;
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		iCount = 0;
		vCTemp.clear();
	}

	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		IOCINEMATICMANAGER->saveFile("검", vCTemp);
	}
}

void CinematicManger::cinematicBossRender()
{
	if(cineMticBossBool == false)
	{
		endingTexure.tex = RM_TEXTURE->getResource("Resource/Maptool/cinema/시네마.png");
		SPRITEMANAGER->renderRectTexture(endingTexure.tex, &endingTexure.rc1, &endingTexure.rc2, 0, 0, 2048, 1024, 0, 0);
	}
}



void CinematicManger::cinematicE4Init()
{
	IOSAVEENDING->loadFile("이벤트4시네마틱");

	for (int i = 0; i < IOSAVEENDING->getCount(); i++)
	{
		Einematic = IOSAVEENDING->findTag("카메라" + to_string(i));

		Ecinematic.push_back(Einematic);
	}
}

void CinematicManger::cinematicE4Load(camera * _camera, bool cinematic)
{
	if (cinematic == false)
	{
		if (ECount < Ecinematic.size())
		{
			D3DXVECTOR3 temp = { Ecinematic[ECount].X, Ecinematic[ECount].Y, Ecinematic[ECount].Z };
			D3DXVECTOR3 tempAngle = { Ecinematic[ECount].rotationX, Ecinematic[ECount].rotationY, Ecinematic[ECount].rotationZ };

			_camera->SetWorldPosition(temp.x, temp.y, temp.z);
			_camera->SetRotateWorld(tempAngle.x, tempAngle.y, tempAngle.z);
			number = Ecinematic[ECount].EningNumber;

			ECount++;

			_camera->updateMatrix();
			_camera->updateCamToDevice();
			_camera->updateFrustum();
		}
		else
		{
			cineMticE4Bool = true;
		}
	}
}

void CinematicManger::cinematicE4Save(camera * _camera)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) number = 0;
	if (KEYMANAGER->isOnceKeyDown('1')) number = 1;
	if (KEYMANAGER->isOnceKeyDown('2')) number = 2;
	if (KEYMANAGER->isOnceKeyDown('3')) number = 3;
	if (KEYMANAGER->isOnceKeyDown('4')) number = 4;
	if (KEYMANAGER->isOnceKeyDown('5')) number = 5;

	if (KEYMANAGER->isToggleKey('M'))
	{
		Etemp.infoName = "카메라" + to_string(ECount);
		Etemp.X = _camera->getCameraPos().x;
		Etemp.Y = _camera->getCameraPos().y;
		Etemp.Z = _camera->getCameraPos().z;
		Etemp.rotationX = D3DXToRadian(_camera->GetAngleX());
		Etemp.rotationY = D3DXToRadian(_camera->GetAngleY());
		Etemp.rotationZ = D3DXToRadian(_camera->GetAngleZ());
		Etemp.EningNumber = number;

		ECTemp.push_back(Etemp);

		ECount++;
	}

	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		ECTemp.clear();
	}


	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		IOSAVEENDING->saveFile("이벤트4시네마틱", ECTemp);
	}
}

void CinematicManger::cinematicE4Render(camera * camera)
{
	if (cineMticE4Bool == false)
	{
		scene4Texure.tex = RM_TEXTURE->getResource("Resource/Maptool/cinema/이벤트4.png");
		SPRITEMANAGER->renderRectTexture(scene4Texure.tex, &scene4Texure.rc1, &scene4Texure.rc2, 0, 0, 2048, 1024, 0, 0);
	}
}



void CinematicManger::cinematicEndingInit()
{
	IOSAVEENDING->loadFile("엔딩시네마틱");

	for (int i = 0; i < IOSAVEENDING->getCount(); i++)
	{
		Einematic = IOSAVEENDING->findTag("카메라" + to_string(i));

		Ecinematic.push_back(Einematic);
	}
}

void CinematicManger::cinematicEndingLoad(camera * _camera)
{
	if (ECount < Ecinematic.size())
	{
		D3DXVECTOR3 temp = { Ecinematic[ECount].X, Ecinematic[ECount].Y, Ecinematic[ECount].Z };
		D3DXVECTOR3 tempAngle = { Ecinematic[ECount].rotationX, Ecinematic[ECount].rotationY, Ecinematic[ECount].rotationZ };

		_camera->SetWorldPosition(temp.x, temp.y, temp.z);
		_camera->SetRotateWorld(tempAngle.x, tempAngle.y, tempAngle.z);
		number = Ecinematic[ECount].EningNumber;

		ECount++;

		_camera->updateMatrix();
		_camera->updateCamToDevice();
		_camera->updateFrustum();
	}
}

void CinematicManger::cinematicEndingSave(camera * _camera)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) number = 0;
	if (KEYMANAGER->isOnceKeyDown('1')) number = 1;
	if (KEYMANAGER->isOnceKeyDown('2')) number = 2;
	if (KEYMANAGER->isOnceKeyDown('3')) number = 3;
	if (KEYMANAGER->isOnceKeyDown('4')) number = 4;
	if (KEYMANAGER->isOnceKeyDown('5')) number = 5;
	if (KEYMANAGER->isOnceKeyDown('6')) number = 6;

	if (KEYMANAGER->isToggleKey('M'))
	{
		Etemp.infoName = "카메라" + to_string(ECount);
		Etemp.X = _camera->getCameraPos().x;
		Etemp.Y = _camera->getCameraPos().y;
		Etemp.Z = _camera->getCameraPos().z;
		Etemp.rotationX = D3DXToRadian(_camera->GetAngleX());
		Etemp.rotationY = D3DXToRadian(_camera->GetAngleY());
		Etemp.rotationZ = D3DXToRadian(_camera->GetAngleZ());
		Etemp.EningNumber = number;

		ECTemp.push_back(Etemp);

		ECount++;
	}

	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		ECTemp.clear();
	}


	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		IOSAVEENDING->saveFile("엔딩시네마틱", ECTemp);
	}
}

void CinematicManger::cinematicEndingRender()
{
	endingTexure.tex = RM_TEXTURE->getResource("Resource/Maptool/cinema/엔딩.png");
	SPRITEMANAGER->renderRectTexture(endingTexure.tex, &endingTexure.rc1, &endingTexure.rc2, 0, 0, 2048, 2048, 0, 0);
}
