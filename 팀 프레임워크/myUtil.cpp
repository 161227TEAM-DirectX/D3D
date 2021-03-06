#include "stdafx.h"
#include "myUtil.h"

namespace myUtil
{
	DWORD maxAnisotropic;		//이방성 필터링 최대 단계
	LPDIRECT3DDEVICE9 device;	//디바이스
	//디바이스 생성함수
	HRESULT CreateDevice()
	{
		/*
		다이렉트3D 초기화
		1. Device를 생성할 IDirect3D9 객체를 얻는다
		2. 하드웨어 정보를 가지고 와서 자신의 정점 프로세스 타입을 정한다
		3. D3DPRESENT_PARAMETERS 구조체 정보를 생성
		4. Device 생성
		*/

		//1. Device를 생성할 IDirect3D9 객체를 얻는다
		//IDirect3D9* d3d9
		LPDIRECT3D9 d3d9;
		d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
		//LPDIRECT3D9 객체얻기를 실패하면 NULL이 참조된다
		if (d3d9 == NULL)
		{
			MessageBox(_hWnd, "Direct3DCreate9() - FAILED", "FAILED", MB_OK);
			return E_FAIL;
		}

		//2. 하드웨어 정보를 가지고 와서 자신의 정점 프로세스 타입을 정한다
		D3DCAPS9 caps;
		//Direct3D9 객체를 통해 비디오 카드의 하드웨어 정보를 가지고 온다
		d3d9->GetDeviceCaps(
			D3DADAPTER_DEFAULT,	//주 디스플레이 그래픽카드 그냥 D3DADAPTER_DEFAULT 사용하면 됨
			D3DDEVTYPE_HAL,		//디바이스타입 설정 그냥 D3DDEVTYPE_HAL
			&caps				//디바이스 정보를 받아올 Direct3D9 포인터
		);

		//그래픽 카드에서 지원되는 이방성 필터링 최대 단계
		maxAnisotropic = caps.MaxAnisotropy;

		//정점계산 처리방식을 지정할 플래그 값
		DWORD vertexProcessing = 0;

		//정점 처리와 정점 광원 처리를 하드웨어에서 지원하냐?
		//D3DCREATE_MULTITHREADED를 해줘야 다이렉트를 멀티쓰레드 환경에서 사용할 수 있다. 
		//이렇게 하지 않으면 다이렉트 관련 함수를 멀티쓰레드에서 사용시 프로그램이 정지할수 있다.
		if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		{
			vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
		}
		else
		{
			vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
		}

		//3. D3DPRESENT_PARAMETERS 구조체 정보를 생성
		//내가 이러한 디바이스를 만들겠다라는 정보
		D3DPRESENT_PARAMETERS d3dpp;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				//뎁스버퍼와 스텐실버퍼의 크기 뎁스24비트, 스텐실8비트
		d3dpp.BackBufferCount = 1;									//백버퍼는 한개
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;					//백버퍼 색상포맷 알파8비트,레드8비트,그린8비트,블루8비트
		d3dpp.BackBufferWidth = WINSIZEX;							//백버퍼 픽셀 가로크기
		d3dpp.BackBufferHeight = WINSIZEY;							//백버퍼 픽셀 세로크기
		d3dpp.EnableAutoDepthStencil = true;						//자동 깊이버퍼 사용여부 (그냥true)
		d3dpp.Flags = 0;											//일단 0
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //화면 주사율 (그냥 D3DPRESENT_RATE_DEFAULT 모니터 주사율과 동일)
		d3dpp.hDeviceWindow = _hWnd;								//디바이스가 출력될 윈도우핸들
		d3dpp.MultiSampleQuality = 0;								//멀티 샘플링 퀄러티
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;				//멀티 샘플링 타입 
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;		//화면 전송 간격
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//화면 스왑 체인 방식
		d3dpp.Windowed = true;										

		//4. Device 생성
		//Direct3d9 객체를 통해서 디바이스를 생성한다

		HRESULT result = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,		//주 디스플레이 그래픽카드 그냥 디폴트
			D3DDEVTYPE_HAL,			//디바이스 타입 설정 그냥 "할"
			_hWnd,					//디바이스 사용할 윈도우 핸들
			vertexProcessing,		//정점 처리방싱에 대한 플래그
			&d3dpp,					//앞에서 정의한 d3dpp 구조체 포인터
			&device);				//얻어올 디바이스 포인터

		if (FAILED(result))
		{
			//디바이스 생성실패시 d3d9 객체 날려야 한다
			SAFE_RELEASE(d3d9);
			
			MessageBox(_hWnd, "CreateDevice() - FAILED", "FAILED", MB_OK);
			return E_FAIL;
		}

		//여기까지 왔으면 디바이스 생성 성공했음
		//더이상 사용되지 않는 d3d9 객체 날려야 한다
		SAFE_RELEASE(d3d9);
	}

	//디바이스 해제함수
	void ReleaseDevice()
	{
		SAFE_RELEASE(device);
		/*
		if (_device != NULL)
		{
			_device->Release();
			_device = NULL;
		}
		*/
	}

	//마우스 위치
	POINT GetMousePos()
	{
		POINT mousePos;
		GetCursorPos(&mousePos); //마우스 스크린 상의 위치를 얻는다
		//스크린 상의 위치를 클라이언트 영역의 범위로 바꾼다
		ScreenToClient(_hWnd, &mousePos);
		return mousePos;
	}
	
	//마우스 위치 세팅
	void SetMousePos(int x, int y)
	{
		POINT setMousePos;
		setMousePos.x = x;
		setMousePos.y = y;

		//클라이언트 상의 위치를 스크린 영역 범위로 바꾼다
		ClientToScreen(_hWnd, &setMousePos);
		//스크린상의 위치로 세팅하기
		SetCursorPos(setMousePos.x, setMousePos.y);
	}

	//value값을 min max사이로 맞추기
	float Clamp(float value, float min, float max)
	{
		if (value < min) return min;
		else if (value > max) return max;
		return value;
	}
	
	//value값을 0 ~ 1 사이로 맞추기
	float Clamp01(float value)
	{
		if (value < 0.0f) return 0.0f;
		else if (value > 1.0f) return 1.0f;
		return value;
	}
	//value값을 -1 ~ 0 사이로 맞추기
	float ClampMinusOnePlusOne(float value)
	{
		if (value < -1.0f) return -1.0f;
		else if (value > 1.0f) return 1.0f;
		return value;
	}
	
	//float 선형보간
	//(t는 0 ~ 1 사이의 값을 받는데..)
	//(t가 0일 수록 from 가까운 값이 리턴되고)
	//(t가 1일 수록 to 가까운 값이 리턴된다)
	float Lerp(float from, float to, float t)
	{
		t = Clamp01(t);
		float delta = to - from;
		return (delta * t) + from;
	}

	//						 5			 9			7 
	float InverseLerp(float head, float rear, float value)
	{
		float delta = rear - head;		//4
		float inValue = value - head;	//2
		if (inValue < 0) inValue = 0;
		return inValue / delta;
	}

	//벡터 선형보간
	D3DXVECTOR3 VecLerp(D3DXVECTOR3 & from, D3DXVECTOR3 & to, float t)
	{
		D3DXVECTOR3 result(
			Lerp(from.x, to.x, t),
			Lerp(from.y, to.y, t),
			Lerp(from.z, to.z, t));
		return result;
	}

	void SetRandomSeed()
	{
		srand(GetTickCount());
	}
	
	float RandomFloatRange(float min, float max)
	{
		float factor = (rand() % 1001) * 0.001f;

		float delta = (max - min);

		float result = (delta * factor) + min;

		return result;
	}
	
	int RandomIntRange(int min, int max)
	{
		int delta = max - min + 1;
		return (rand() % delta) + min;
	}

	//정점의 노말을 계산해주는 함수
	void ComputeNormal(D3DXVECTOR3 * pNorams, const D3DXVECTOR3 * pVertices, int verticesNum, const DWORD * pIndices, int indicesNum)
	{
		//노말벡터 초기화
		ZeroMemory(pNorams, sizeof(D3DXVECTOR3) * verticesNum);

		//삼각형 갯수
		DWORD triNum = indicesNum / 3;
		for (DWORD i = 0; i < triNum; i++)
		{
			//해당 삼각형의 정점 인덱스
			DWORD i0 = pIndices[(i * 3) + 0];
			DWORD i1 = pIndices[(i * 3) + 1];
			DWORD i2 = pIndices[(i * 3) + 2];

			//정점 3개
			D3DXVECTOR3 v0 = pVertices[i0];
			D3DXVECTOR3 v1 = pVertices[i1];
			D3DXVECTOR3 v2 = pVertices[i2];

			//Edge
			D3DXVECTOR3 edge1 = v1 - v0;
			D3DXVECTOR3 edge2 = v2 - v0;

			//Cross
			D3DXVECTOR3 cross;
			D3DXVec3Cross(&cross, &edge1, &edge2);

			//Normal
			D3DXVECTOR3 normal;
			D3DXVec3Normalize(&normal, &cross);

			//증가 시킨다.
			pNorams[i0] += normal;
			pNorams[i1] += normal;
			pNorams[i2] += normal;
		}

		//최종 적으로 Normalvector 정규화한다.
		for (DWORD i = 0; i < verticesNum; i++)
		{
			D3DXVec3Normalize(&pNorams[i], &pNorams[i]);
		}
	}

	//탄젠트와 바이노말 계산
	void ComputeTangentBinormal(D3DXVECTOR3 * outTangets, D3DXVECTOR3 * outBinormals, const D3DXVECTOR3 * pPositions, const D3DXVECTOR3 * pNormals, const D3DXVECTOR2 * pUVs, const DWORD * pIndices, DWORD NumTris, DWORD NumVertices)
	{
		//탄젠트 바이노말 초기화
		ZeroMemory(outTangets, sizeof(D3DXVECTOR3) * NumVertices);
		ZeroMemory(outBinormals, sizeof(D3DXVECTOR3) * NumVertices);

		//임시 Tangent Binormal 배열
		D3DXVECTOR3* pTangents = new D3DXVECTOR3[NumVertices];
		D3DXVECTOR3* pBinormals = new D3DXVECTOR3[NumVertices];

		//임시 Tangent Binormal 배열 초기화
		ZeroMemory(pTangents, sizeof(D3DXVECTOR3) * NumVertices);
		ZeroMemory(pBinormals, sizeof(D3DXVECTOR3) * NumVertices);

		//일단 삼각형 수대로....
		for (DWORD a = 0; a < NumTris; a++)
		{
			//해당 삼각형의 인덱스
			DWORD i0 = pIndices[a * 3 + 0];
			DWORD i1 = pIndices[a * 3 + 1];
			DWORD i2 = pIndices[a * 3 + 2];

			//해당 삼각형의 정점위치
			D3DXVECTOR3 p0 = pPositions[i0];
			D3DXVECTOR3 p1 = pPositions[i1];
			D3DXVECTOR3 p2 = pPositions[i2];

			//해당 삼각형의 UV
			D3DXVECTOR2 uv0 = pUVs[i0];
			D3DXVECTOR2 uv1 = pUVs[i1];
			D3DXVECTOR2 uv2 = pUVs[i2];

			//각변의 Edge
			D3DXVECTOR3 edge1 = p1 - p0;
			D3DXVECTOR3 edge2 = p2 - p0;

			//UV Edge
			D3DXVECTOR2 uvEdge1 = uv1 - uv0;
			D3DXVECTOR2 uvEdge2 = uv2 - uv0;

			// 위의 정보로 다음과 같은 공식이 성립
			// edge1 = ( uvEdge1.x ) * Tangent + ( uvEdge1.y ) * Binormal;
			// edge2 = ( uvEdge2.x ) * Tangent + ( uvEdge2.y ) * Binormal;

			// 다음과 같이 치환
			// E1 = edge1;
			// E2 = edge2;
			// U1 = uvEdge1.x;
			// V1 = uvEdge1.y;
			// U2 = uvEdge2.x;
			// V2 = uvEdge2.y;
			// T = Tangent;
			// B = Binormal;

			// E1 = U1 * T + V1 * B;
			// E2 = U2 * T + V2 * B;

			// | E1 |   | U1 , V1 | | T |
			// |    | = |         | |   |
			// | E2 |   | U2 , V2 | | B |

			// | T |          1        |  V2 , -V1 | | E1 |
			// |   | = --------------- |           | |    |
			// | B |    U1*V2 - V1*U2  | -U2 ,  U1 | | E2 |

			// R = 1 / U1*V2 - V1*U2;

			// T = ( ( E1 * V2 ) + ( E2 * -V1 ) ) * R
			// B = ( ( E1 * -U2 ) + ( E2 * U1 ) ) * R

			float r = 1.0f / ((uvEdge1.x * uvEdge2.y) - (uvEdge1.y * uvEdge2.x));

			//Tangent
			D3DXVECTOR3 t = ((edge1 * uvEdge2.y) + (edge2 * -uvEdge1.y)) * r;
			D3DXVec3Normalize(&t, &t);

			//Binormal 
			D3DXVECTOR3 b = ((edge1 * -uvEdge2.x) + (edge2 * uvEdge1.x)) * r;
			D3DXVec3Normalize(&b, &b);

			//탄젠트 바이노말 임시 배열에 추가
			pTangents[i0] += t;
			pTangents[i1] += t;
			pTangents[i2] += t;
			pBinormals[i0] += b;
			pBinormals[i1] += b;
			pBinormals[i2] += b;
		}

		//Binormal Tangent 노말에 직교화
		for (int i = 0; i < NumVertices; i++) 
		{
			D3DXVECTOR3 n = pNormals[i];

			//Tangent 그람슈미트 직교
			D3DXVECTOR3 t = pTangents[i] - (D3DXVec3Dot(&pTangents[i], &n) * n);
			D3DXVec3Normalize(&t, &t);

			//노말과 직교화된 T 와 외적하여 B
			D3DXVECTOR3 b;
			D3DXVec3Cross(&b, &n, &t);
			D3DXVec3Normalize(&b, &b);

			outTangets[i] = t;
			outBinormals[i] = b;
		}

		//임시 배열 삭제
		SAFE_DELETE_ARRAY(pTangents);
		SAFE_DELETE_ARRAY(pBinormals);
	}
	DWORD FloatToDWORD(float f)
	{
		float* pFloat = &f;

		DWORD* pDword = (DWORD*)pFloat;

		return *pDword;
	}



	void RectMake(float cx, float cy, float nWidth, float nHeight, bool isFill, D3DCOLOR dwColor)
	{
		D3DXMATRIXA16 m_matTrans;
		D3DXMatrixIdentity(&m_matTrans);

		D3DXVECTOR3 v ={ cx,cy,0.0f };
		D3DXMatrixTranslation(&m_matTrans, v.x, v.y, v.z);

		DWORD dwPrev = 0;
		_device->SetTexture(0, NULL);
		_device->GetRenderState(D3DRS_LIGHTING, &dwPrev);
		_device->SetRenderState(D3DRS_LIGHTING, false);

		int nCnt = 0;
		ST_RHWC_VERTEX aVertex[5];

		if (isFill)
		{
			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = dwColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41 + nWidth, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = dwColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42 + nHeight, 0, 1);
			aVertex[nCnt++].c = dwColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41 + nWidth, m_matTrans._42 + nHeight, 0, 1);
			aVertex[nCnt++].c = dwColor;

			_device->SetFVF(ST_RHWC_VERTEX::FVF);
			_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, aVertex, sizeof(ST_RHWC_VERTEX));
			_device->SetRenderState(D3DRS_LIGHTING, (bool)dwPrev);
		}
		else
		{
			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = dwColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42 + nHeight, 0, 1);
			aVertex[nCnt++].c = dwColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41 + nWidth, m_matTrans._42 + nHeight, 0, 1);
			aVertex[nCnt++].c = dwColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41 + nWidth, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = dwColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = dwColor;

			_device->SetFVF(ST_RHWC_VERTEX::FVF);
			_device->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, aVertex, sizeof(ST_RHWC_VERTEX));
			_device->SetRenderState(D3DRS_LIGHTING, (bool)dwPrev);
		}
	}



	void RectMakeCenter(float cCenterX, float cCenterY, float nWidth, float nHeight, bool isFill, D3DCOLOR dwColor)
	{
		D3DXMATRIXA16 m_matTrans;
		D3DXMatrixIdentity(&m_matTrans);

		D3DXVECTOR3 v ={ cCenterX - nWidth / 2,cCenterY - nHeight / 2,0.0f };
		D3DXMatrixTranslation(&m_matTrans, v.x, v.y, v.z);

		DWORD dwPrev = 0;
		_device->SetTexture(0, NULL);
		_device->GetRenderState(D3DRS_LIGHTING, &dwPrev);
		_device->SetRenderState(D3DRS_LIGHTING, false);

		int nCnt = 0;
		ST_RHWC_VERTEX aVertex[5];

		if (isFill)
		{
			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = dwColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41 + nWidth, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = dwColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42 + nHeight, 0, 1);
			aVertex[nCnt++].c = dwColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41 + nWidth, m_matTrans._42 + nHeight, 0, 1);
			aVertex[nCnt++].c = dwColor;

			_device->SetFVF(ST_RHWC_VERTEX::FVF);
			_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, aVertex, sizeof(ST_RHWC_VERTEX));
			_device->SetRenderState(D3DRS_LIGHTING, (bool)dwPrev);
		}
		else
		{
			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = dwColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42 + nHeight, 0, 1);
			aVertex[nCnt++].c = dwColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41 + nWidth, m_matTrans._42 + nHeight, 0, 1);
			aVertex[nCnt++].c = dwColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41 + nWidth, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = dwColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = dwColor;

			_device->SetFVF(ST_RHWC_VERTEX::FVF);
			_device->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, aVertex, sizeof(ST_RHWC_VERTEX));
			_device->SetRenderState(D3DRS_LIGHTING, (bool)dwPrev);
		}
	}

	void LineMake(float startX, float startY, float endX, float endY, D3DCOLOR dwColor)
	{
		D3DXMATRIXA16 m_matTrans;
		D3DXMatrixIdentity(&m_matTrans);

		D3DXVECTOR3 v ={ startX,startY,0.0f };
		D3DXMatrixTranslation(&m_matTrans, v.x, v.y, v.z);

		DWORD dwPrev = 0;
		_device->SetTexture(0, NULL);
		_device->GetRenderState(D3DRS_LIGHTING, &dwPrev);
		_device->SetRenderState(D3DRS_LIGHTING, false);

		int nCnt = 0;
		ST_RHWC_VERTEX aVertex[2];

		aVertex[nCnt].p = D3DXVECTOR4(startX, startY, 0, 1);
		aVertex[nCnt++].c = dwColor;

		aVertex[nCnt].p = D3DXVECTOR4(endX, endY, 0, 1);
		aVertex[nCnt++].c = dwColor;

		_device->SetFVF(ST_RHWC_VERTEX::FVF);
		_device->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, aVertex, sizeof(ST_RHWC_VERTEX));
		_device->SetRenderState(D3DRS_LIGHTING, (bool)dwPrev);
	}
}