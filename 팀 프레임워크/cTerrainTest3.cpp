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
	// ���� ����
	//=====================================================
	m_csTerrain.setHeightmap("height_base128");
	m_csTerrain.setTile0("tileTest11");
	m_csTerrain.setTile1("tileTest9");
	m_csTerrain.setTile2("tileTest9");
	m_csTerrain.setTile3("tileTest9");
	m_csTerrain.setSplat("splat_red_base");
	//m_csTerrain.SetHtChangeSign(-1);		//������ �ø����� ��������
	m_csTerrain.SetHtChangeRange(5);		//�������� ������	
											//m_csTerrain.SetHtChangeValue(3.0f);	//�󸶸�ŭ ������ ����
											//m_csTerrain.SetIsSmoothing(false);	//�������� �Ұ���
	m_csTerrain.setting();

	//=====================================================
	// ��ŷ��ġ �ʱ�ȭ
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

		//Terrain �̶� Rayüũ
		m_csTerrain.isIntersectRay(&m_vHitPos, &ray);

		//Terrain���� ��ŷ�� ���� �ε����� �����´�.
		m_vSelectIdx = m_csTerrain.getIdx(m_vHitPos.x, m_vHitPos.z);

		//Terrain���� ��ŷ�� �ε��� �κ��� �ø���.
		//���� ���´� ����Ʈ�� �Ҵ� Ʈ������̹Ƿ� �ѹ� ������ ���� ���尡 ����ȴ�.
		m_csTerrain.changeHeight(m_vSelectIdx.x, m_vSelectIdx.y);

		//Ű�� ������ ���� ���� ����Ʈ�� �Ҵ��� ���� �ʴ´�.
		m_csTerrain.SetIsQuad(false);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		//Ű�� ���� ����Ʈ�� �Ҵ� ���θ� Ʈ��� �����Ѵ�.
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
	//������ �׸���.
	m_csTerrain.render(&m_csCamera, &m_csLightDir);

	//Hit ��ġ�� �������
	GIZMOMANAGER->WireSphere(m_vHitPos, 0.3f, RED);

	//�ǽð� ������
	FONTMANAGER->fontOut("��ŷ ��ǥ:%.3f %.3f %.3f", m_vHitPos.x, m_vHitPos.y, m_vHitPos.z, 0, 20, YELLOW);
	FONTMANAGER->fontOut("���� ��ü ���ؽ� ����: %d", m_csTerrain.GetTotalVerNum(), 0, 40, YELLOW);
	FONTMANAGER->fontOut("���� ���μ��� ���ؽ� ����: %d %d", m_csTerrain.GetVerNumX(), m_csTerrain.GetVerNumZ(), 0, 60, YELLOW);
	FONTMANAGER->fontOut("������ ����: %d", m_csTerrain.GetSmoothLevel(), 0, 80, YELLOW);

}
