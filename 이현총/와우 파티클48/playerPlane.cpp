#include "stdafx.h"
#include "playerPlane.h"


void playerPlane::baseObjectUpdate()
{
	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
	{
		//ÃÊ´ç 90µµ
		float rotDelta = D3DXToRadian(90) * _timeDelta;
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_transform->RotateWorld(0, -rotDelta, 0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_transform->RotateWorld(0, rotDelta, 0);
		}
	}
	else
	{
		float moveDelta = 5.0f * _timeDelta;
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_transform->MovePositionWorld(0, -moveDelta, 0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_transform->MovePositionWorld(0, moveDelta, 0);
		}
	}
}
