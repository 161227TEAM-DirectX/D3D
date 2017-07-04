#pragma once
#include "iGameNode.h"

class cCameraTest : public iGameNode
{
private:
	camera			m_csCamera;
	terrain			m_csTerrain;
	lightDirection	m_csLightDir;

	bool	m_isCamMove = false;
	float	m_fCamMoveV = 1.0f;
	int		m_nCamDirMoveV = 1;

	dx::transform	m_csTransEast;		//��
	dx::transform	m_csTransWest;		//��
	dx::transform	m_csTransSouth;		//��
	dx::transform	m_csTransNorth;		//��
	dx::transform	m_csTransCenter;	//�߾�
	vector<dx::transform>	m_vecTrans;


	D3DXVECTOR3	m_vecCamSavePos ={ 0,0,0 };	//ī�޶� ��ġ ����
	D3DXVECTOR3 m_vecCamSaveAngle ={ 0,0,0 };	//ī�޶� ���� ����
	float		m_fCamSaveNowAngleH = 0.0f;	//ī�޶� ����ޱ� ����
	float		m_fCamSaveNowAngleV = 0.0f;	//ī�޶� �����ޱ� ����


	enum eCamType
	{
		E_CAM_GAME,
		E_CAM_WORLD,
	};
	eCamType m_eCamType = E_CAM_GAME;

	enum eCamAction
	{
		E_CAM_NONE,
		E_CAM_MOVE,
	};
	eCamAction m_eCamAction = E_CAM_NONE;

	enum eWayPoint
	{
		E_WAYPOINT_NONE,
		E_WAYPOINT_EAST,
		E_WAYPOINT_WEST,
		E_WAYPOINT_SOUTH,
		E_WAYPOINT_NORTH,
		E_WAYPOINT_CURRENT
	};
	eWayPoint m_eWayPoint = E_WAYPOINT_NONE;

	float m_fDirWWayPoint = 0;		//��������Ʈ �������
	float m_fDirHWayPoint = 0;		//��������Ʈ ��������

public:
	cCameraTest();
	virtual ~cCameraTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

