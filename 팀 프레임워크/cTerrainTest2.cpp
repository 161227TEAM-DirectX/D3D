#include "stdafx.h"
#include "cTerrainTest2.h"


cTerrainTest2::cTerrainTest2()
	: m_sCurTex("")							//현재 색칠할 텍스쳐
	, m_vSelectPos(0.0f, 0.0f, 0.0f)		//피킹한 위치 좌표
	, m_vSelectColor(0.0f, 0.0f, 0.0f)		//피킹한 스플랫 색상
	, m_vSelectIdx(0.0f, 0.0f)				//피킹한 버텍스 번호(x,z)
	, m_nSplatRange(0)						//색칠할 범위
	, m_vSelectRangePos(0.0f, 0.0f, 0.0f)		//선택한 범위체크그림 위치
{
	ZeroMemory(&m_pSplatBase, sizeof(m_pSplatBase));
}


cTerrainTest2::~cTerrainTest2()
{
}

HRESULT cTerrainTest2::init()
{
	DXIMG_MANAGER->GetDxImg("tileTest0_mapTool")->SetPosition(D3DXVECTOR3(200, 20, 0));
	DXIMG_MANAGER->GetDxImg("tileTest1_mapTool")->SetPosition(D3DXVECTOR3(300, 20, 0));
	DXIMG_MANAGER->GetDxImg("tileTest2_mapTool")->SetPosition(D3DXVECTOR3(400, 20, 0));
	DXIMG_MANAGER->GetDxImg("tileTest3_mapTool")->SetPosition(D3DXVECTOR3(500, 20, 0));

	m_csTerrain.setHeightmap("height_base256");
	m_csTerrain.setTile0("tileTest0");
	m_csTerrain.setTile1("tileTest1");
	m_csTerrain.setTile2("tileTest2");
	m_csTerrain.setTile3("tileTest3");
	m_csTerrain.setSplat("splat_base");
	m_csTerrain.setHeightscale(100.0f);
	//m_csTerrain.setTileNum(1);
	//m_csTerrain.SetIsVertexDraw(true);
	m_csTerrain.setting();

	m_vHitPos = D3DXVECTOR3(0, 0, 0);

	m_pSplatBase = TEXTURE_MANAGER->GetTexture("splat_base");
	//m_pSplatBase = TEXTURE_MANAGER->GetTexture("splat_test0");
	//m_pSplatBase = TEXTURE_MANAGER->GetTexture("splat_test1");
	//m_pSplatBase = TEXTURE_MANAGER->GetTexture("splat_test2");
	//m_pSplatBase = TEXTURE_MANAGER->GetTexture("splat_test3");
	m_csTerrain.setSplat(m_pSplatBase);

	DXIMG_MANAGER->GetDxImg("rangeTest00")->SetPosition(D3DXVECTOR3(800, 0, 0));
	DXIMG_MANAGER->GetDxImg("rangeTest00")->SetDrawBoundingBox(true);

	DXIMG_MANAGER->GetDxImg("rangeTest01")->SetPosition(D3DXVECTOR3(900, 0, 0));
	DXIMG_MANAGER->GetDxImg("rangeTest01")->SetDrawBoundingBox(true);

	DXIMG_MANAGER->GetDxImg("rangeTest02")->SetPosition(D3DXVECTOR3(1000, 0, 0));
	DXIMG_MANAGER->GetDxImg("rangeTest02")->SetDrawBoundingBox(true);

	DXIMG_MANAGER->GetDxImg("rangeTest03")->SetPosition(D3DXVECTOR3(1100, 0, 0));
	DXIMG_MANAGER->GetDxImg("rangeTest03")->SetDrawBoundingBox(true);

	DXIMG_MANAGER->GetDxImg("rangeTest04")->SetPosition(D3DXVECTOR3(1200, 0, 0));
	DXIMG_MANAGER->GetDxImg("rangeTest04")->SetDrawBoundingBox(true);

	//일단 0단계로 범위그림체크 위치를 설정해두자.
	m_vSelectRangePos = DXIMG_MANAGER->GetDxImg("rangeTest00")->GetPosition();

	return S_OK;
}

void cTerrainTest2::release()
{
}

void cTerrainTest2::update()
{
	m_csCamera.updateBase(true);

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&DXIMG_MANAGER->GetDxImg("tileTest0_mapTool")->getRect(), GetMousePos()))
		{
			m_sCurTex = "tileTest0_mapTool";
			m_vSelectPos = DXIMG_MANAGER->GetDxImg(m_sCurTex)->GetPosition();
		}

		else if (PtInRect(&DXIMG_MANAGER->GetDxImg("tileTest1_mapTool")->getRect(), GetMousePos()))
		{
			m_sCurTex = "tileTest1_mapTool";
			m_vSelectPos = DXIMG_MANAGER->GetDxImg(m_sCurTex)->GetPosition();
		}

		else if (PtInRect(&DXIMG_MANAGER->GetDxImg("tileTest2_mapTool")->getRect(), GetMousePos()))
		{
			m_sCurTex = "tileTest2_mapTool";
			m_vSelectPos = DXIMG_MANAGER->GetDxImg(m_sCurTex)->GetPosition();
		}

		else if (PtInRect(&DXIMG_MANAGER->GetDxImg("tileTest3_mapTool")->getRect(), GetMousePos()))
		{
			m_sCurTex = "tileTest3_mapTool";
			m_vSelectPos = DXIMG_MANAGER->GetDxImg(m_sCurTex)->GetPosition();
		}


		//범위를 조정한다.
		else if (PtInRect(&DXIMG_MANAGER->GetDxImg("rangeTest00")->getRect(), GetMousePos()))
		{
			m_nSplatRange = 0;
			m_vSelectRangePos = DXIMG_MANAGER->GetDxImg("rangeTest00")->GetPosition();
		}
		else if (PtInRect(&DXIMG_MANAGER->GetDxImg("rangeTest01")->getRect(), GetMousePos()))
		{
			m_nSplatRange = 1;
			m_vSelectRangePos = DXIMG_MANAGER->GetDxImg("rangeTest01")->GetPosition();
		}
		else if (PtInRect(&DXIMG_MANAGER->GetDxImg("rangeTest02")->getRect(), GetMousePos()))
		{
			m_nSplatRange = 2;
			m_vSelectRangePos = DXIMG_MANAGER->GetDxImg("rangeTest02")->GetPosition();
		}
		else if (PtInRect(&DXIMG_MANAGER->GetDxImg("rangeTest03")->getRect(), GetMousePos()))
		{
			m_nSplatRange = 3;
			m_vSelectRangePos = DXIMG_MANAGER->GetDxImg("rangeTest03")->GetPosition();
		}
		else if (PtInRect(&DXIMG_MANAGER->GetDxImg("rangeTest04")->getRect(), GetMousePos()))
		{
			m_nSplatRange = 4;
			m_vSelectRangePos = DXIMG_MANAGER->GetDxImg("rangeTest04")->GetPosition();
		}

		else
		{
			Ray ray;
			POINT ptMousePos = GetMousePos();
			D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
			m_csCamera.computeRay(&ray, &screenPos);

			//Terrain 이랑 Ray체크
			m_csTerrain.isIntersectRay(&m_vHitPos, &ray);

			//Terrain에서 피킹한 곳의 인덱스를 가져온다.
			m_vSelectIdx = m_csTerrain.getIdx(m_vHitPos.x, m_vHitPos.z);

			//현재 정점x,y에서 스플랫 색상을 가져온다.
			m_vSelectColor = m_csTerrain.selectSplatColor("splat_base", m_vSelectIdx.x, m_vSelectIdx.y);


			//============================================================================================
			//
			//============================================================================================
			//int x = m_vSelectIdx.x;
			//int z = m_vSelectIdx.y;

			D3DLOCKED_RECT lockRect;
			//m_pSplatBase = TEXTURE_MANAGER->GetTexture("splat_base");
			m_pSplatBase->LockRect(0, &lockRect, 0, 0);

			for (int z = m_vSelectIdx.y - m_nSplatRange; z <= m_vSelectIdx.y + m_nSplatRange; z++)
			{
				for (int x = m_vSelectIdx.x - m_nSplatRange; x <= m_vSelectIdx.x + m_nSplatRange; x++)
				{
					//해당 픽셀의 컬러 값을 얻는다.
					DWORD* pStart = (DWORD*)lockRect.pBits;	//(DWORD 형으로 형변환된 lock 된 이미지지의 시작 주소
					DWORD dwColor = *(pStart + (z * (lockRect.Pitch / 4) + x));

					if (m_sCurTex == "tileTest0_mapTool")
					{
						*(pStart + (z * (lockRect.Pitch / 4) + x)) = 255 << 16;		// R    
					}
					else if (m_sCurTex == "tileTest1_mapTool")
					{
						*(pStart + (z * (lockRect.Pitch / 4) + x)) = 255 << 8;		// G  
					}
					else if (m_sCurTex == "tileTest2_mapTool")
					{
						*(pStart + (z * (lockRect.Pitch / 4) + x)) = 255 << 4;		// B   
					}
					else if (m_sCurTex == "tileTest3_mapTool")
					{
						*(pStart + (z * (lockRect.Pitch / 4) + x)) = 0;				// Bk  
					}

					//*(pStart + (z * (lockRect.Pitch / 4) + x)) = 255 << 16;		// R    
					//*(pStart + (z * (lockRect.Pitch / 4) + x)) = 255 << 8;		// G    
					//*(pStart + (z * (lockRect.Pitch / 4) + x)) = 255 << 4;		// B    
					//*(pStart + (z * (lockRect.Pitch / 4) + x)) = 0;				// Bk 
				}
			}
			m_pSplatBase->UnlockRect(0);
		}
	}


	if (m_sCurTex != "")
	{
		DXIMG_MANAGER->GetDxImg("tileTest_Select")->SetPosition(D3DXVECTOR3(m_vSelectPos.x, m_vSelectPos.y, 0.0f));
		DXIMG_MANAGER->GetDxImg("checkTest00")->SetPosition(D3DXVECTOR3(m_vSelectRangePos.x, m_vSelectRangePos.y, 0.0f));
	}


	//기본 마우스커서를 안보이게 하고(원래는 로딩부터 해야겠지)
	ShowCursor(FALSE);
	//현재 마우스커서 위치에 커서이미지 위치를 갱신한다.
	DXIMG_MANAGER->GetDxImg("GrieverCursor")->SetPosition(D3DXVECTOR3(GetMousePos().x, GetMousePos().y, 0));
}

void cTerrainTest2::render()
{
	//지형을 그리자.(여기에 꽤 많은 일들이 일어난다.)
	m_csTerrain.render(&m_csCamera, &m_csLightDir);

	//Hit 위치에 구만들기
	GIZMOMANAGER->WireSphere(m_vHitPos, 0.5f, SKY);

	//텍스쳐_맵툴 이미지를 그리자.
	DXIMG_MANAGER->GetDxImg("tileTest0_mapTool")->render();
	DXIMG_MANAGER->GetDxImg("tileTest1_mapTool")->render();
	DXIMG_MANAGER->GetDxImg("tileTest2_mapTool")->render();
	DXIMG_MANAGER->GetDxImg("tileTest3_mapTool")->render();

	//현재 들고있는 텍스쳐가 비어있지 않으면
	if (m_sCurTex != "")
	{
		//텍스쳐맵툴 이미지에 테두리를 그린다.
		DXIMG_MANAGER->GetDxImg("tileTest_Select")->render();
	}

	//실시간 디버깅용
	FONTMANAGER->fontOut("현재 텍스쳐:%s", m_sCurTex.c_str(), 0, 100, YELLOW);
	FONTMANAGER->fontOut("마우스 좌표:%.3f %.3f %.3f", m_vHitPos.x, m_vHitPos.y, m_vHitPos.z, 0, 120, YELLOW);
	FONTMANAGER->fontOut("스플랫색상: %.f %.f %.f", m_vSelectColor.x, m_vSelectColor.y, m_vSelectColor.z, 0, 140, YELLOW);
	FONTMANAGER->fontOut("현재 x,y: %f %f", m_vSelectIdx.x, m_vSelectIdx.y, 0, 160, YELLOW);


	DXIMG_MANAGER->GetDxImg("rangeTest00")->render();
	DXIMG_MANAGER->GetDxImg("rangeTest01")->render();
	DXIMG_MANAGER->GetDxImg("rangeTest02")->render();
	DXIMG_MANAGER->GetDxImg("rangeTest03")->render();
	DXIMG_MANAGER->GetDxImg("rangeTest04")->render();

	if (m_sCurTex != "")
	{
		DXIMG_MANAGER->GetDxImg("checkTest00")->render();
	}

	//마우스 커서를 그리자.
	DXIMG_MANAGER->GetDxImg("GrieverCursor")->render();
}