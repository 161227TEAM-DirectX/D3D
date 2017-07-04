#include "stdafx.h"
#include "cTerrainTest3.h"


cTerrainTest3::cTerrainTest3()
{
}


cTerrainTest3::~cTerrainTest3()
{
}

HRESULT cTerrainTest3::init()
{
	//=====================================================
	// 지형 설정
	//=====================================================
	m_csTerrain.setHeightmap("height_base128");
	m_csTerrain.setTile0("tileTest11");
	m_csTerrain.setTile1("tileTest9");
	m_csTerrain.setTile2("tileTest9");
	m_csTerrain.setTile3("tileTest9");
	m_csTerrain.setSplat("splat_red_base");
	//m_csTerrain.SetHtChangeSign(-1);		//지형을 올릴건지 내릴건지
	m_csTerrain.SetHtChangeRange(5);		//지형변경 범위는	
											//m_csTerrain.SetHtChangeValue(3.0f);	//얼마만큼 변경할 건지
											//m_csTerrain.SetIsSmoothing(false);	//스무싱을 할건지
	m_csTerrain.setting();

	//=====================================================
	// 피킹위치 초기화
	//=====================================================
	m_vHitPos = D3DXVECTOR3(0, 0, 0);

	return S_OK;
}

void cTerrainTest3::release()
{
}

void cTerrainTest3::update()
{
	m_csCamera.updateBase(true);

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		m_csCamera.computeRay(&ray, &screenPos);

		//Terrain 이랑 Ray체크
		m_csTerrain.isIntersectRay(&m_vHitPos, &ray);

		//Terrain에서 피킹한 곳의 인덱스를 가져온다.
		m_vSelectIdx = m_csTerrain.getIdx(m_vHitPos.x, m_vHitPos.z);

		//Terrain에서 피킹한 인덱스 부분을 올린다.
		//현재 상태는 쿼드트리 할당 트루상태이므로 한번 세팅할 때는 쿼드가 적용된다.
		m_csTerrain.changeHeight(m_vSelectIdx.x, m_vSelectIdx.y);

		//키를 누르고 있을 때는 쿼드트리 할당을 하지 않는다.
		m_csTerrain.SetIsQuad(false);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		//키를 떼면 쿼드트리 할당 여부를 트루로 설정한다.
		m_csTerrain.SetIsQuad(true);
	}
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		m_csTerrain.SetHtChangeSign(1);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		m_csTerrain.SetHtChangeSign(-1);
	}
}

void cTerrainTest3::render()
{
	//지형을 그리자.
	m_csTerrain.render(&m_csCamera, &m_csLightDir);

	//Hit 위치에 구만들기
	GIZMOMANAGER->WireSphere(m_vHitPos, 0.3f, RED);

	//실시간 디버깅용
	FONTMANAGER->fontOut("피킹 좌표:%.3f %.3f %.3f", m_vHitPos.x, m_vHitPos.y, m_vHitPos.z, 0, 20, YELLOW);
	FONTMANAGER->fontOut("지형 전체 버텍스 개수: %d", m_csTerrain.GetTotalVerNum(), 0, 40, YELLOW);
	FONTMANAGER->fontOut("지형 가로세로 버텍스 개수: %d %d", m_csTerrain.GetVerNumX(), m_csTerrain.GetVerNumZ(), 0, 60, YELLOW);
	FONTMANAGER->fontOut("스무싱 레벨: %d", m_csTerrain.GetSmoothLevel(), 0, 80, YELLOW);

}
