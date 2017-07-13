#include "stdafx.h"
#include "cUICinema.h"


cUICinema::cUICinema()
	: m_fCutscnGauge(0.0f)				//�ƾ� ������
	, m_fCutscnMaxGauge(160.0f)			//�ƾ� �ƽ�������(�������� ���� �����δ�.)
	, m_fCutscnSpeed(1.5f)				//�ƾ� �ӵ�
	, m_nCutscnDir(-1)					//�ƾ� ����(���������� �ö󰡴���)
	, m_fCutscnUp(-300.0f)				//�� �ƾ����� �̹��� ������ǥ(y��)	
	, m_fCutscnDown(WINSIZEY)			//�Ʒ� �ƾ����� �̹��� ������ǥ(y��)
	, m_fCutscnUpEnd(-140.0f)			//�� �ƾ����� �̹��� ����ǥ(y��)
	, m_fCutscnDownEnd(WINSIZEY - 160)	//�Ʒ� �ƾ����� �̹��� ����ǥ(y��)
	, m_nStrCount(0)					//�ڸ� �ε���(���پ� �о�´�.)
	, m_nTimeCount(0)					//�̰ɷ� ��� m_nTimeMax�� ���ų� Ŀ���� ���� �ڸ�����
	, m_nTimeMax(200)					//ī��Ʈ �ƽ�
	, m_isCutStart(false)				//�ƾ��� �����ߴ��� ����
{
}


cUICinema::~cUICinema()
{
}

void cUICinema::init()
{
	DXIMG_MANAGER->GetDxImg("�̺�Ʈ��_��")->SetPosition(D3DXVECTOR3(0, m_fCutscnUp, 0));
	DXIMG_MANAGER->GetDxImg("�̺�Ʈ��_�Ʒ�")->SetPosition(D3DXVECTOR3(0, m_fCutscnDown, 0));

	m_fCutscnGauge = m_fCutscnMaxGauge;

	//============================================================================
	// �ڸ��� ��������....
	//============================================================================
	//char ioString[128];
	//memset(ioString, 0, sizeof(ioString));

	//sprintf(ioString, "%s.txt", "ResourceUI/test/�ƾ����");
	//ifstream inFile(ioString);


	//assert(!inFile.fail() && "������ �����ϴ�.");

	//while (!inFile.eof())
	//{
	//	inFile.getline(ioString, 128, '\n');
	//	m_vecString.push_back(ioString);
	//}

	////�ڸ� ��Ʈ
	//FONTMANAGER->addFont("�ü�ü", "�ü�ü", 30);
}

void cUICinema::update()
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



	//============================================================================
	// �ڸ� ������Ʈ
	//============================================================================
	//if (m_nTimeCount++ >= m_nTimeMax && m_isCutStart)
	//{
	//	if (m_nStrCount < m_vecString.size() - 1)
	//	{
	//		m_nStrCount++;
	//		m_nTimeCount = 0;
	//	}
	//}
}

void cUICinema::render()
{
	DXIMG_MANAGER->GetDxImg("�̺�Ʈ��_��")->render();
	DXIMG_MANAGER->GetDxImg("�̺�Ʈ��_�Ʒ�")->render();


	//============================================================================
	// �ڸ� ����
	//============================================================================
	//if (m_isCutStart)
	//{
	//	FONTMANAGER->fontOutWithStyle("�ü�ü", m_vecString[m_nStrCount], 400, 800, WHITE);
	//}
}
