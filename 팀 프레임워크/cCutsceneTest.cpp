#include "stdafx.h"
#include "cCutsceneTest.h"


cCutsceneTest::cCutsceneTest()
{
}


cCutsceneTest::~cCutsceneTest()
{
}

HRESULT cCutsceneTest::init()
{
	DXIMG_MANAGER->GetDxImg("�̺�Ʈ��_��")->SetPosition(D3DXVECTOR3(0, m_fCutscnUp, 0));
	DXIMG_MANAGER->GetDxImg("�̺�Ʈ��_�Ʒ�")->SetPosition(D3DXVECTOR3(0, m_fCutscnDown, 0));

	m_fCutscnGauge = m_fCutscnMaxGauge;


	char ioString[128];
	memset(ioString, 0, sizeof(ioString));

	sprintf(ioString, "%s.txt", "ResourceUI/test/�ƾ����");
	ifstream inFile(ioString);


	assert(!inFile.fail() && "������ �����ϴ�.");

	while (!inFile.eof())
	{
		inFile.getline(ioString, 128, '\n');
		m_vecString.push_back(ioString);
	}

	FONTMANAGER->addFont("�ü�ü", "�ü�ü", 30);

	return S_OK;
}

void cCutsceneTest::release()
{
}

void cCutsceneTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		m_fCutscnGauge = 0;
		m_nCutscnDir *= -1;
	}

	if (m_fCutscnGauge < m_fCutscnMaxGauge)
	{
		m_fCutscnGauge+=m_fCutscnSpeed;

		if (m_nCutscnDir == 1)
		{
			DXIMG_MANAGER->GetDxImg("�̺�Ʈ��_��")->SetPosition(D3DXVECTOR3(0, m_fCutscnUp + m_nCutscnDir*m_fCutscnGauge, 0));
			DXIMG_MANAGER->GetDxImg("�̺�Ʈ��_�Ʒ�")->SetPosition(D3DXVECTOR3(0, m_fCutscnDown - m_nCutscnDir*m_fCutscnGauge, 0));
		}

		if (m_nCutscnDir == -1)
		{
			DXIMG_MANAGER->GetDxImg("�̺�Ʈ��_��")->SetPosition(D3DXVECTOR3(0, m_fCutscnUpEnd + m_nCutscnDir*m_fCutscnGauge, 0));
			DXIMG_MANAGER->GetDxImg("�̺�Ʈ��_�Ʒ�")->SetPosition(D3DXVECTOR3(0, m_fCutscnDownEnd - m_nCutscnDir*m_fCutscnGauge, 0));
		}
	}

	if (DXIMG_MANAGER->GetDxImg("�̺�Ʈ��_��")->GetPosition().y + 1 >= m_fCutscnUpEnd && !m_isCutStart)
	{
		m_nTimeCount++;
		if (m_nTimeCount >= 300)
		{
			m_nTimeCount = 0;
			m_isCutStart = true;
		}
	}

	if (m_nTimeCount++ >= m_nTimeMax && m_isCutStart)
	{
		if (m_nStrCount < m_vecString.size() - 1)
		{
			m_nStrCount++;
			m_nTimeCount = 0;
		}
	}
}

void cCutsceneTest::render()
{
	DXIMG_MANAGER->GetDxImg("�̺�Ʈ��_��")->render();
	DXIMG_MANAGER->GetDxImg("�̺�Ʈ��_�Ʒ�")->render();

	//FONTMANAGER->fontOut("���콺 ��ġ: %d %d", GetMousePos().x, GetMousePos().y, 0, 20, RED);

	//FONTMANAGER->fontOut(m_vecString[0], 613, 811, WHITE);

	//FONTMANAGER->fontOut("%.f", m_fCutscnGauge, 0, 40, WHITE);

	if (m_isCutStart)
	{
		FONTMANAGER->fontOutWithStyle("�ü�ü", m_vecString[m_nStrCount], 400, 800, WHITE);
	}

	//for (int i=0; i < m_vecString.size(); i++)
	//{
	//	//FONTMANAGER->fontOut(m_vecString[i], WINSIZEX / 2, 50 + 20 * i, WHITE);
	//	FONTMANAGER->fontOutWithStyle("�ü�ü",m_vecString[i], WINSIZEX / 2, 50 + 30 * i, WHITE);
	//}
}
