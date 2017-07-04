#include "stdafx.h"
#include "cCameraTest.h"


cCameraTest::cCameraTest()
{
}


cCameraTest::~cCameraTest()
{
}

HRESULT cCameraTest::init()
{
	//���� ����
	m_csTerrain.setHeightmap("height_base128");
	m_csTerrain.setTile0("tileTest12");
	m_csTerrain.setTile1("tileTest10");
	m_csTerrain.setTile2("tileTest10");
	m_csTerrain.setTile3("tileTest10");
	m_csTerrain.setSplat("splat_red_base");
	m_csTerrain.setTileNum(1);
	m_csTerrain.setting();

	m_csCamera.SetWorldPosition(0.0f, 10.0f, 0.0f);

	//m_csCamera.SetRotateLocal(D3DXToRadian(30.0f),0.0f, 0.0f);


	//m_csCamera.SetRotateLocal(0.0f, D3DXToRadian(30.0f), 0.0f);
	//m_csCamera.SetRotateWorld(0.0f, D3DXToRadian(30.0f), 0.0f);
	//m_csCamera.linkNowAngleH(30.0f);

	m_csTransEast.SetWorldPosition(D3DXVECTOR3(50, 0, 0));		//����
	m_csTransWest.SetWorldPosition(D3DXVECTOR3(-40, 0, 0));		//����
	m_csTransSouth.SetWorldPosition(D3DXVECTOR3(0, 0, -40));	//����
	m_csTransNorth.SetWorldPosition(D3DXVECTOR3(0, 0, 50));		//����
	m_csTransCenter.SetWorldPosition(D3DXVECTOR3(0, 0, 0));		//�߾�


	DXIMG_MANAGER->GetDxImg("worldmapTest")->SetPosition(D3DXVECTOR3(WINSIZEX - 270, 20, 0));
	//DXIMG_MANAGER->GetDxImg("worldmapTest")->SetDrawBoundingBox(true);

	DXIMG_MANAGER->GetDxImg("gamemapTest")->SetPosition(D3DXVECTOR3(WINSIZEX - 170, 20, 0));
	//DXIMG_MANAGER->GetDxImg("gamemapTest")->SetDrawBoundingBox(true);

	DXIMG_MANAGER->GetDxImg("markCenter")->SetCenterDraw(true);
	DXIMG_MANAGER->GetDxImg("markEast")->SetCenterDraw(true);
	DXIMG_MANAGER->GetDxImg("markWest")->SetCenterDraw(true);
	DXIMG_MANAGER->GetDxImg("markSouth")->SetCenterDraw(true);
	DXIMG_MANAGER->GetDxImg("markNorth")->SetCenterDraw(true);

	return S_OK;
}

void cCameraTest::release()
{
}

void cCameraTest::update()
{
	m_csCamera.updateBase(true);

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//ī�޶��� ���� � �������(���������� ������� ����������)
		switch (m_eCamType)
		{
		case E_CAM_GAME:
			if (PtInRect(&DXIMG_MANAGER->GetDxImg("worldmapTest")->getRect(), GetMousePos()))
			{
				m_vecCamSavePos = m_csCamera.GetWorldPosition();
				m_vecCamSaveAngle = D3DXVECTOR3(m_csCamera.GetAngleX(), m_csCamera.GetAngleY(), m_csCamera.GetAngleZ());
				m_fCamSaveNowAngleH = m_csCamera.GetNowAngleH();
				m_fCamSaveNowAngleV = m_csCamera.GetNowAngleV();

				if (m_csCamera.GetWorldPosition().y < 120)
				{
					m_eCamAction = E_CAM_NONE;
					m_eWayPoint = E_WAYPOINT_NONE;
					m_fDirWWayPoint = 0;
					m_fDirHWayPoint = 0;
					m_isCamMove = true;
					m_nCamDirMoveV = 1;

					m_csCamera.SetWorldPosition(0.0f, 0.0f, 0.0f);
					m_csCamera.SetRotateWorld(D3DXToRadian(90.0f), 0.0f, 0.0f);
					m_csCamera.linkNowAngleV(90.0f);
				}
			}
			break;

		case E_CAM_WORLD:

			//�߾� ��ũ
			if (PtInRect(&DXIMG_MANAGER->GetDxImg("markCenter")->getRect(), GetMousePos()))
			{

			}
			//���� ��ũ
			else if (PtInRect(&DXIMG_MANAGER->GetDxImg("markEast")->getRect(), GetMousePos()))
			{
				m_eCamAction = E_CAM_MOVE;
				m_eWayPoint = E_WAYPOINT_EAST;
				m_isCamMove = true;
				m_nCamDirMoveV = -1;

				m_vecCamSavePos = m_csTransEast.GetWorldPosition();
			}
			//���� ��ũ
			else if (PtInRect(&DXIMG_MANAGER->GetDxImg("markWest")->getRect(), GetMousePos()))
			{
				m_eCamAction = E_CAM_MOVE;
				m_eWayPoint = E_WAYPOINT_WEST;
				m_isCamMove = true;
				m_nCamDirMoveV = -1;

				m_vecCamSavePos = m_csTransWest.GetWorldPosition();
			}
			//���� ��ũ
			else if (PtInRect(&DXIMG_MANAGER->GetDxImg("markSouth")->getRect(), GetMousePos()))
			{
				m_eCamAction = E_CAM_MOVE;
				m_eWayPoint = E_WAYPOINT_SOUTH;
				m_isCamMove = true;
				m_nCamDirMoveV = -1;

				m_vecCamSavePos = m_csTransSouth.GetWorldPosition();
			}
			//���� ��ũ
			else if (PtInRect(&DXIMG_MANAGER->GetDxImg("markNorth")->getRect(), GetMousePos()))
			{
				m_eCamAction = E_CAM_MOVE;
				m_eWayPoint = E_WAYPOINT_NORTH;
				m_isCamMove = true;
				m_nCamDirMoveV = -1;

				m_vecCamSavePos = m_csTransNorth.GetWorldPosition();
			}


			//���Ӹ����� ���ư��� ��ư�� ���� ��
			if (PtInRect(&DXIMG_MANAGER->GetDxImg("gamemapTest")->getRect(), GetMousePos()))
			{
				if (m_csCamera.GetWorldPosition().y >= 120)
				{
					m_eCamAction = E_CAM_MOVE;
					m_isCamMove = true;
					m_nCamDirMoveV = -1;
				}
			}
			break;
		}
	}


	//����ʰ� ���� ��ȯ ���̴�.
	if (m_isCamMove)
	{
		//� ��������Ʈ�� ������
		switch (m_eWayPoint)
		{
		case E_WAYPOINT_NONE:



			break;

			//���� ǥ������ ���ٸ�...
		case E_WAYPOINT_EAST:
			//ī�޶��� x��ǥ�� ���� ǥ�ĺ��� Ŀ����
			if (m_csCamera.GetWorldPosition().x >= m_csTransEast.GetWorldPosition().x)
			{
				//ī�޶� x��ǥ�� ������Ű��
				m_csCamera.SetWorldPosition(m_csTransEast.GetWorldPosition().x,
											m_csCamera.GetWorldPosition().y,
											m_csCamera.GetWorldPosition().z);
				//��������Ʈ�� ������ �������� 0���� �ϰ�
				m_fDirWWayPoint = 0;
			}
			else
			{
				//��������Ʈ�� ������ �������� -0.45f
				m_fDirWWayPoint = -0.45f;
			}
			break;

			//���� ǥ������ ���ٸ�...
		case E_WAYPOINT_WEST:
			//ī�޶��� x��ǥ�� ���� ǥ�ĺ��� Ŀ����
			if (m_csCamera.GetWorldPosition().x <= m_csTransWest.GetWorldPosition().x)
			{
				//ī�޶� x��ǥ�� ������Ű��
				m_csCamera.SetWorldPosition(m_csTransWest.GetWorldPosition().x,
											m_csCamera.GetWorldPosition().y,
											m_csCamera.GetWorldPosition().z);
				//��������Ʈ�� ������ �������� 0���� �ϰ�
				m_fDirWWayPoint = 0;
			}
			else
			{
				//��������Ʈ�� ������ �������� -0.45f
				m_fDirWWayPoint = +0.36f;
			}
			break;

			//���� ǥ������ ���ٸ�...
		case E_WAYPOINT_SOUTH:
			//ī�޶��� z��ǥ�� ���� ǥ�ĺ��� Ŀ����
			if (m_csCamera.GetWorldPosition().z <= m_csTransSouth.GetWorldPosition().z)
			{
				//ī�޶� z��ǥ�� ������Ű��
				m_csCamera.SetWorldPosition(m_csCamera.GetWorldPosition().x,
											m_csCamera.GetWorldPosition().y,
											m_csTransSouth.GetWorldPosition().z);
				//��������Ʈ�� ������ �������� 0���� �ϰ�
				m_fDirHWayPoint = 0;
			}
			else
			{
				//��������Ʈ�� ������ �������� -0.45f
				m_fDirHWayPoint = +0.36f;
			}
			break;

			//���� ǥ������ ���ٸ�...
		case E_WAYPOINT_NORTH:
			//ī�޶��� z��ǥ�� ���� ǥ�ĺ��� �۾�����
			if (m_csCamera.GetWorldPosition().z >= m_csTransNorth.GetWorldPosition().z)
			{
				//ī�޶� z��ǥ�� ������Ű��
				m_csCamera.SetWorldPosition(m_csCamera.GetWorldPosition().x,
											m_csCamera.GetWorldPosition().y,
											m_csTransNorth.GetWorldPosition().z);
				//��������Ʈ�� ������ �������� 0���� �ϰ�
				m_fDirHWayPoint = 0;
			}
			else
			{
				//��������Ʈ�� ������ �������� -0.45f
				m_fDirHWayPoint = -0.45f;
			}
			break;
		}

		//ī�޶� �̵�
		m_csCamera.SetWorldPosition(m_csCamera.GetWorldPosition().x + m_fDirWWayPoint * m_nCamDirMoveV,
									m_csCamera.GetWorldPosition().y + m_fCamMoveV * m_nCamDirMoveV,
									m_csCamera.GetWorldPosition().z + m_fDirHWayPoint * m_nCamDirMoveV);

		//��������� ���ڴ��� ��� �׸� �ö� �����̴�.
		if (m_csCamera.GetWorldPosition().y > 120 && m_eCamType == E_CAM_GAME)
		{
			m_isCamMove = false;
			m_eCamType = E_CAM_WORLD;

			float worldMapIconX;
			float worldMapIconZ;

			int worldMapWidth = 824;
			int worldMapHeight = 824;
			int worldMapStartX = 388;
			int worldMapStartZ = 38;

			//��
			worldMapIconX = (worldMapWidth *(m_csTransEast.GetWorldPosition().x + m_csTerrain.GetTerrainSizeX() / 2)) / m_csTerrain.GetTerrainSizeX() + worldMapStartX;
			worldMapIconZ = (worldMapHeight *(m_csTransEast.GetWorldPosition().z + m_csTerrain.GetTerrainSizeZ() / 2)) / m_csTerrain.GetTerrainSizeZ() + worldMapStartZ;
			DXIMG_MANAGER->GetDxImg("markEast")->SetPosition(D3DXVECTOR3(worldMapIconX, worldMapIconZ, 0));



			//��
			worldMapIconX = (worldMapWidth *(m_csTransWest.GetWorldPosition().x + m_csTerrain.GetTerrainSizeX() / 2)) / m_csTerrain.GetTerrainSizeX() + worldMapStartX;
			worldMapIconZ = (worldMapHeight *(m_csTransWest.GetWorldPosition().z + m_csTerrain.GetTerrainSizeZ() / 2)) / m_csTerrain.GetTerrainSizeZ() + worldMapStartZ;
			DXIMG_MANAGER->GetDxImg("markWest")->SetPosition(D3DXVECTOR3(worldMapIconX, worldMapIconZ, 0));



			//��
			worldMapIconX = (worldMapWidth *(m_csTransSouth.GetWorldPosition().x + m_csTerrain.GetTerrainSizeX() / 2)) / m_csTerrain.GetTerrainSizeX() + worldMapStartX;
			worldMapIconZ = (worldMapHeight *(-m_csTransSouth.GetWorldPosition().z + m_csTerrain.GetTerrainSizeZ() / 2)) / m_csTerrain.GetTerrainSizeZ() + worldMapStartZ;
			DXIMG_MANAGER->GetDxImg("markSouth")->SetPosition(D3DXVECTOR3(worldMapIconX, worldMapIconZ, 0));



			//��
			worldMapIconX = (worldMapWidth *(m_csTransNorth.GetWorldPosition().x + m_csTerrain.GetTerrainSizeX() / 2)) / m_csTerrain.GetTerrainSizeX() + worldMapStartX;
			worldMapIconZ = (worldMapHeight *(-m_csTransNorth.GetWorldPosition().z + m_csTerrain.GetTerrainSizeZ() / 2)) / m_csTerrain.GetTerrainSizeZ() + worldMapStartZ;
			DXIMG_MANAGER->GetDxImg("markNorth")->SetPosition(D3DXVECTOR3(worldMapIconX, worldMapIconZ, 0));



			//�߾�
			worldMapIconX = (worldMapWidth *(m_csTransCenter.GetWorldPosition().x + m_csTerrain.GetTerrainSizeX() / 2)) / m_csTerrain.GetTerrainSizeX() + worldMapStartX;
			worldMapIconZ = (worldMapHeight *(m_csTransCenter.GetWorldPosition().z + m_csTerrain.GetTerrainSizeZ() / 2)) / m_csTerrain.GetTerrainSizeZ() + worldMapStartZ;
			DXIMG_MANAGER->GetDxImg("markCenter")->SetPosition(D3DXVECTOR3(worldMapIconX, worldMapIconZ, 0));
		}

		//���Ӹ����� ���ڴ��� ��� �׸� ������ �����̴�.
		if (m_csCamera.GetWorldPosition().y < 10.0f && m_eCamType == E_CAM_WORLD)
		{
			//��������Ʈ ���°� ���̶��
			if (m_eWayPoint == E_WAYPOINT_NONE)
			{
				m_csCamera.SetWorldPosition(m_vecCamSavePos);

				m_csCamera.SetRotateWorld(D3DXToRadian(m_vecCamSaveAngle.x),
										  D3DXToRadian(m_vecCamSaveAngle.y),
										  D3DXToRadian(m_vecCamSaveAngle.z));
				m_csCamera.linkNowAngleH(m_fCamSaveNowAngleH);
				m_csCamera.linkNowAngleV(m_fCamSaveNowAngleV);
			}
			//���� ǥ���̶��
			else if (m_eWayPoint == E_WAYPOINT_EAST)
			{
				m_csCamera.SetWorldPosition(m_csTransEast.GetWorldPosition().x,
											10.0f,
											m_csTransEast.GetWorldPosition().z);
				m_eWayPoint = E_WAYPOINT_NONE;
			}
			//���� ǥ���̶��
			else if (m_eWayPoint == E_WAYPOINT_WEST)
			{
				m_csCamera.SetWorldPosition(m_csTransWest.GetWorldPosition().x,
											10.0f,
											m_csTransWest.GetWorldPosition().z);
				m_eWayPoint = E_WAYPOINT_NONE;
			}
			//���� ǥ���̶��
			else if (m_eWayPoint == E_WAYPOINT_SOUTH)
			{
				m_csCamera.SetWorldPosition(m_csTransSouth.GetWorldPosition().x,
											10.0f,
											m_csTransSouth.GetWorldPosition().z);

				m_eWayPoint = E_WAYPOINT_NONE;
			}
			//���� ǥ���̶��
			else if (m_eWayPoint == E_WAYPOINT_NORTH)
			{
				m_csCamera.SetWorldPosition(m_csTransNorth.GetWorldPosition().x,
											10.0f,
											m_csTransNorth.GetWorldPosition().z);

				m_eWayPoint = E_WAYPOINT_NONE;
			}

			m_isCamMove = false;
			m_eCamType = E_CAM_GAME;
		}
	}
}

void cCameraTest::render()
{
	m_csTerrain.render(&m_csCamera, &m_csLightDir);

	switch (m_eCamType)
	{
	case E_CAM_GAME:
		DXIMG_MANAGER->GetDxImg("worldmapTest")->render();
		break;
	case E_CAM_WORLD:
		DXIMG_MANAGER->GetDxImg("gamemapTest")->render();

		if (m_eCamAction == E_CAM_NONE)
		{
			DXIMG_MANAGER->GetDxImg("markCenter")->render();
			DXIMG_MANAGER->GetDxImg("markEast")->render();
			DXIMG_MANAGER->GetDxImg("markWest")->render();
			DXIMG_MANAGER->GetDxImg("markSouth")->render();
			DXIMG_MANAGER->GetDxImg("markNorth")->render();
		}
		break;
	}




	GIZMOMANAGER->WireSphere(m_csTransEast.GetWorldPosition(), 1.0f, RED);
	GIZMOMANAGER->WireSphere(m_csTransWest.GetWorldPosition(), 1.0f, ORANGE);
	GIZMOMANAGER->WireSphere(m_csTransSouth.GetWorldPosition(), 1.0f, GREEN);
	GIZMOMANAGER->WireSphere(m_csTransNorth.GetWorldPosition(), 1.0f, BLUE);
	GIZMOMANAGER->WireSphere(m_csTransCenter.GetWorldPosition(), 1.0f, BLACK);




	FONTMANAGER->fontOut("ī�޶� ��ġ: %.3f %.3f %.3f",
						 m_csCamera.GetWorldPosition().x,
						 m_csCamera.GetWorldPosition().y,
						 m_csCamera.GetWorldPosition().z,
						 0, 20, GREEN);
	FONTMANAGER->fontOut("ī�޶� ���� X: %.f", m_csCamera.GetAngleX(), 0, 40, GREEN);
	FONTMANAGER->fontOut("ī�޶� ���� Y: %.f", m_csCamera.GetAngleY(), 0, 60, GREEN);
	FONTMANAGER->fontOut("ī�޶� ���� Z: %.f", m_csCamera.GetAngleZ(), 0, 80, GREEN);

	FONTMANAGER->fontOut("����ޱ�: %f", m_csCamera.GetNowAngleH(), 0, 100, GREEN);
	FONTMANAGER->fontOut("�����ޱ�: %f", m_csCamera.GetNowAngleV(), 0, 120, GREEN);

	FONTMANAGER->fontOut("����� ī�޶� ��ġ: %.3f %.3f %.3f", m_vecCamSavePos.x, m_vecCamSavePos.y, m_vecCamSavePos.z, 0, 160, GREEN);
	FONTMANAGER->fontOut("����� ī�޶� ����: %.3f %.3f %.3f", m_vecCamSaveAngle.x, m_vecCamSaveAngle.y, m_vecCamSaveAngle.z, 0, 180, GREEN);
	FONTMANAGER->fontOut("����� ����ޱ�: %f", m_fCamSaveNowAngleH, 0, 200, GREEN);
	FONTMANAGER->fontOut("����� �����ޱ�: %f", m_fCamSaveNowAngleV, 0, 220, GREEN);

	FONTMANAGER->fontOut("���콺 ��ġ: %d %d", GetMousePos().x, GetMousePos().y, 0, 240, RED);

	FONTMANAGER->fontOut("%.3f %.3f %.3f",
						 m_csTransSouth.GetWorldPosition().x,
						 m_csTransSouth.GetWorldPosition().y,
						 m_csTransSouth.GetWorldPosition().z, 0, 260, RED
	);
}
