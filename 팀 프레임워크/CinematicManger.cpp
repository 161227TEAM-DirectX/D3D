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
}

void CinematicManger::cinematicInit()
{
	//IOCINEMATICMANAGER->loadFile("시네마틱");

	//for (int i = 0; i < IOCINEMATICMANAGER->getCount(); i++)
	//{
	//	cinematic = IOCINEMATICMANAGER->findTag("카메라" + to_string(i));

	//	vcinematic.push_back(cinematic);
	//}
}

void CinematicManger::cinematicLoad(D3DXVECTOR3 * position, camera * camera, dx::transform * transform)
{
	if (iCount < vcinematic.size())
	{
		lookPos = *position;

		D3DXVECTOR3 temp = { vcinematic[iCount].X, vcinematic[iCount].Y, vcinematic[iCount].Z };

		D3DXVec3TransformCoord(&temp, &temp, &transform->GetWorldRotateMatrix());

		camera->LookPosition((lookPos + D3DXVECTOR3(0, vcinematic[iCount].Height, 0)));
		camera->SetWorldPosition((position->x + temp.x), position->y + temp.y, (position->z + temp.z));

		iCount++;

		camera->updateCamToDevice();
	}
}

void CinematicManger::cinematicSave(D3DXVECTOR3 * position, camera * camera)
{
	lookPos = *position;

	RotateAngle += RotateRadian *_timeDelta;

	cameraPositionX = lookPos.x + cos(RotateAngle)* cameraXZ;
	cameraPositionY = lookPos.y + cameraY;
	cameraPositionZ = lookPos.z + sin(RotateAngle)*cameraXZ;

	camera->LookPosition(lookPos + cameraHeight);
	camera->SetWorldPosition(cameraPositionX, cameraPositionY, cameraPositionZ);
	camera->updateCamToDevice();

	//위로 올라가는거
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD1))
	{
		cameraHeight.y += 0.03f;
		cameraY += 0.03f;
	}
	//아래로 내려가는거
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD2))
	{
		cameraHeight.y -= 0.03f;
		cameraY -= 0.03f;
	}
	//각도를 위로올리는거
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD4))
	{
		cameraHeight.y += 0.03f;
	}
	//각도를 아래로내리는거
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD5))
	{
		cameraHeight.y -= 0.03f;
	}
	//약간 위를 중심으로 위로돌리기,위를중심으로 아래로돌리기
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD7))
	{
		cameraY += 0.03f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD8))
	{
		cameraY -= 0.03f;
	}

	//캠확대 , 축소
	if (KEYMANAGER->isStayKeyDown('C')) 	cameraXZ += 0.05f;
	if (KEYMANAGER->isStayKeyDown('V')) 	cameraXZ -= 0.05f;

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
		Ctemp.X = camera->getCameraPos().x;
		Ctemp.Y = camera->getCameraPos().y;
		Ctemp.Z = camera->getCameraPos().z;
		Ctemp.Height = cameraHeight.y;

		vCTemp.push_back(Ctemp);

		iCount++;
	}

	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		IOCINEMATICMANAGER->saveFile("시네마틱", vCTemp);
	}
}

void CinematicManger::cinematicEInit()
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

	    _camera->SetWorldPosition(temp.x, temp.y,temp.z);
		_camera->SetRotateWorld(tempAngle.x, tempAngle.y, tempAngle.z);
		number = Ecinematic[ECount].EningNumber;

		ECount++;

		_camera->updateCamToDevice();
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

	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		IOSAVEENDING->saveFile("엔딩시네마틱", ECTemp);
	}
}

void CinematicManger::cinemaRender(camera * camera)
{
	//texture.tex = RM_TEXTURE->getResource("Resources/maptoolui/시네마.png");
	//SPRITEMANAGER->renderRectTexture(texture.tex, &texture.rc1, &texture.rc2, 0, 0, 2048, 1024, 0, 0);

	//FONTMANAGER->fontOut(to_string(camera->GetWorldPosition().x), 100, 100, D3DCOLOR_XRGB(255, 255, 255));
}
