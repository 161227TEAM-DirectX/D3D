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

	dx::transform	m_csTransEast;		//동
	dx::transform	m_csTransWest;		//서
	dx::transform	m_csTransSouth;		//남
	dx::transform	m_csTransNorth;		//북
	dx::transform	m_csTransCenter;	//중앙
	vector<dx::transform>	m_vecTrans;


	D3DXVECTOR3	m_vecCamSavePos ={ 0,0,0 };	//카메라 위치 저장
	D3DXVECTOR3 m_vecCamSaveAngle ={ 0,0,0 };	//카메라 각도 저장
	float		m_fCamSaveNowAngleH = 0.0f;	//카메라 수평앵글 저장
	float		m_fCamSaveNowAngleV = 0.0f;	//카메라 수직앵글 저장


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

	float m_fDirWWayPoint = 0;		//웨이포인트 수평방향
	float m_fDirHWayPoint = 0;		//웨이포인트 수직방향

public:
	cCameraTest();
	virtual ~cCameraTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

