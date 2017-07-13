#include "stdafx.h"
#include "cUICinema.h"


cUICinema::cUICinema()
	: m_fCutscnGauge(0.0f)				//컷씬 게이지
	, m_fCutscnMaxGauge(160.0f)			//컷씬 맥스게이지(높을수록 많이 움직인다.)
	, m_fCutscnSpeed(1.5f)				//컷씬 속도
	, m_nCutscnDir(-1)					//컷씬 방향(내려오는지 올라가는지)
	, m_fCutscnUp(-300.0f)				//위 컷씬검정 이미지 시작좌표(y축)	
	, m_fCutscnDown(WINSIZEY)			//아래 컷씬검정 이미지 시작좌표(y축)
	, m_fCutscnUpEnd(-140.0f)			//위 컷씬검정 이미지 끝좌표(y축)
	, m_fCutscnDownEnd(WINSIZEY - 160)	//아래 컷씬검정 이미지 끝좌표(y축)
	, m_nStrCount(0)					//자막 인덱스(한줄씩 읽어온다.)
	, m_nTimeCount(0)					//이걸로 세어서 m_nTimeMax와 같거나 커지면 다음 자막으로
	, m_nTimeMax(200)					//카운트 맥스
	, m_isCutStart(false)				//컷씬이 시작했는지 여부
{
}


cUICinema::~cUICinema()
{
}

void cUICinema::init()
{
	DXIMG_MANAGER->GetDxImg("이벤트씬_위")->SetPosition(D3DXVECTOR3(0, m_fCutscnUp, 0));
	DXIMG_MANAGER->GetDxImg("이벤트씬_아래")->SetPosition(D3DXVECTOR3(0, m_fCutscnDown, 0));

	m_fCutscnGauge = m_fCutscnMaxGauge;

	//============================================================================
	// 자막을 넣으려면....
	//============================================================================
	//char ioString[128];
	//memset(ioString, 0, sizeof(ioString));

	//sprintf(ioString, "%s.txt", "ResourceUI/test/컷씬대사");
	//ifstream inFile(ioString);


	//assert(!inFile.fail() && "파일이 없습니다.");

	//while (!inFile.eof())
	//{
	//	inFile.getline(ioString, 128, '\n');
	//	m_vecString.push_back(ioString);
	//}

	////자막 폰트
	//FONTMANAGER->addFont("궁서체", "궁서체", 30);
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
			DXIMG_MANAGER->GetDxImg("이벤트씬_위")->SetPosition(D3DXVECTOR3(0, m_fCutscnUp + m_nCutscnDir*m_fCutscnGauge, 0));
			DXIMG_MANAGER->GetDxImg("이벤트씬_아래")->SetPosition(D3DXVECTOR3(0, m_fCutscnDown - m_nCutscnDir*m_fCutscnGauge, 0));
		}

		if (m_nCutscnDir == -1)
		{
			DXIMG_MANAGER->GetDxImg("이벤트씬_위")->SetPosition(D3DXVECTOR3(0, m_fCutscnUpEnd + m_nCutscnDir*m_fCutscnGauge, 0));
			DXIMG_MANAGER->GetDxImg("이벤트씬_아래")->SetPosition(D3DXVECTOR3(0, m_fCutscnDownEnd - m_nCutscnDir*m_fCutscnGauge, 0));
		}
	}

	if (DXIMG_MANAGER->GetDxImg("이벤트씬_위")->GetPosition().y + 1 >= m_fCutscnUpEnd && !m_isCutStart)
	{
		m_nTimeCount++;
		if (m_nTimeCount >= 300)
		{
			m_nTimeCount = 0;
			m_isCutStart = true;
		}
	}



	//============================================================================
	// 자막 업데이트
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
	DXIMG_MANAGER->GetDxImg("이벤트씬_위")->render();
	DXIMG_MANAGER->GetDxImg("이벤트씬_아래")->render();


	//============================================================================
	// 자막 렌더
	//============================================================================
	//if (m_isCutStart)
	//{
	//	FONTMANAGER->fontOutWithStyle("궁서체", m_vecString[m_nStrCount], 400, 800, WHITE);
	//}
}
