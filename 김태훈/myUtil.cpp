#include "stdafx.h"
#include "myUtil.h"

namespace myUtil
{
	DWORD maxAnisotropic;		//�̹漺 ���͸� �ִ� �ܰ�
	LPDIRECT3DDEVICE9 device;	//����̽�
	//����̽� �����Լ�
	HRESULT CreateDevice()
	{
		/*
		���̷�Ʈ3D �ʱ�ȭ
		1. Device�� ������ IDirect3D9 ��ü�� ��´�
		2. �ϵ���� ������ ������ �ͼ� �ڽ��� ���� ���μ��� Ÿ���� ���Ѵ�
		3. D3DPRESENT_PARAMETERS ����ü ������ ����
		4. Device ����
		*/

		//1. Device�� ������ IDirect3D9 ��ü�� ��´�
		//IDirect3D9* d3d9
		LPDIRECT3D9 d3d9;
		d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
		//LPDIRECT3D9 ��ü��⸦ �����ϸ� NULL�� �����ȴ�
		if (d3d9 == NULL)
		{
			MessageBox(_hWnd, "Direct3DCreate9() - FAILED", "FAILED", MB_OK);
			return E_FAIL;
		}

		//2. �ϵ���� ������ ������ �ͼ� �ڽ��� ���� ���μ��� Ÿ���� ���Ѵ�
		D3DCAPS9 caps;
		//Direct3D9 ��ü�� ���� ���� ī���� �ϵ���� ������ ������ �´�
		d3d9->GetDeviceCaps(
			D3DADAPTER_DEFAULT,	//�� ���÷��� �׷���ī�� �׳� D3DADAPTER_DEFAULT ����ϸ� ��
			D3DDEVTYPE_HAL,		//����̽�Ÿ�� ���� �׳� D3DDEVTYPE_HAL
			&caps				//����̽� ������ �޾ƿ� Direct3D9 ������
		);

		//�׷��� ī�忡�� �����Ǵ� �̹漺 ���͸� �ִ� �ܰ�
		maxAnisotropic = caps.MaxAnisotropy;

		//������� ó������� ������ �÷��� ��
		DWORD vertexProcessing = 0;
		//���� ó���� ���� ���� ó���� �ϵ����� �����ϳ�?
		if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		{
			vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		}
		else
		{
			vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		}

		//3. D3DPRESENT_PARAMETERS ����ü ������ ����
		//���� �̷��� ����̽��� ����ڴٶ�� ����
		D3DPRESENT_PARAMETERS d3dpp;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				//�������ۿ� ���ٽǹ����� ũ�� ����24��Ʈ, ���ٽ�8��Ʈ
		d3dpp.BackBufferCount = 1;									//����۴� �Ѱ�
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;					//����� �������� ����8��Ʈ,����8��Ʈ,�׸�8��Ʈ,���8��Ʈ
		d3dpp.BackBufferWidth = WINSIZEX;							//����� �ȼ� ����ũ��
		d3dpp.BackBufferHeight = WINSIZEY;							//����� �ȼ� ����ũ��
		d3dpp.EnableAutoDepthStencil = true;						//�ڵ� ���̹��� ��뿩�� (�׳�true)
		d3dpp.Flags = 0;											//�ϴ� 0
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //ȭ�� �ֻ��� (�׳� D3DPRESENT_RATE_DEFAULT ����� �ֻ����� ����)
		d3dpp.hDeviceWindow = _hWnd;								//����̽��� ��µ� �������ڵ�
		d3dpp.MultiSampleQuality = 0;								//��Ƽ ���ø� ����Ƽ
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;				//��Ƽ ���ø� Ÿ�� 
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;		//ȭ�� ���� ����
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//ȭ�� ���� ü�� ���
		d3dpp.Windowed = true;										

		//4. Device ����
		//Direct3d9 ��ü�� ���ؼ� ����̽��� �����Ѵ�

		HRESULT result = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,		//�� ���÷��� �׷���ī�� �׳� ����Ʈ
			D3DDEVTYPE_HAL,			//����̽� Ÿ�� ���� �׳� "��"
			_hWnd,					//����̽� ����� ������ �ڵ�
			vertexProcessing,		//���� ó����̿� ���� �÷���
			&d3dpp,					//�տ��� ������ d3dpp ����ü ������
			&device);				//���� ����̽� ������

		if (FAILED(result))
		{
			//����̽� �������н� d3d9 ��ü ������ �Ѵ�
			SAFE_RELEASE(d3d9);
			
			MessageBox(_hWnd, "CreateDevice() - FAILED", "FAILED", MB_OK);
			return E_FAIL;
		}

		//������� ������ ����̽� ���� ��������
		//���̻� ������ �ʴ� d3d9 ��ü ������ �Ѵ�
		SAFE_RELEASE(d3d9);
	}

	//����̽� �����Լ�
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

	//���콺 ��ġ
	POINT GetMousePos()
	{
		POINT mousePos;
		GetCursorPos(&mousePos); //���콺 ��ũ�� ���� ��ġ�� ��´�
		//��ũ�� ���� ��ġ�� Ŭ���̾�Ʈ ������ ������ �ٲ۴�
		ScreenToClient(_hWnd, &mousePos);
		return mousePos;
	}
	
	//���콺 ��ġ ����
	void SetMousePos(int x, int y)
	{
		POINT setMousePos;
		setMousePos.x = x;
		setMousePos.y = y;

		//Ŭ���̾�Ʈ ���� ��ġ�� ��ũ�� ���� ������ �ٲ۴�
		ClientToScreen(_hWnd, &setMousePos);
		//��ũ������ ��ġ�� �����ϱ�
		SetCursorPos(setMousePos.x, setMousePos.y);
	}

	//value���� min max���̷� ���߱�
	float Clamp(float value, float min, float max)
	{
		if (value < min) return min;
		else if (value > max) return max;
		return value;
	}
	
	//value���� 0 ~ 1 ���̷� ���߱�
	float Clamp01(float value)
	{
		if (value < 0.0f) return 0.0f;
		else if (value > 1.0f) return 1.0f;
		return value;
	}
	//value���� -1 ~ 0 ���̷� ���߱�
	float ClampMinusOnePlusOne(float value)
	{
		if (value < -1.0f) return -1.0f;
		else if (value > 1.0f) return 1.0f;
		return value;
	}
	
	//float ��������
	//(t�� 0 ~ 1 ������ ���� �޴µ�..)
	//(t�� 0�� ���� from ����� ���� ���ϵǰ�)
	//(t�� 1�� ���� to ����� ���� ���ϵȴ�)
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

	//���� ��������
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

	//������ �븻�� ������ִ� �Լ�
	void ComputeNormal(D3DXVECTOR3 * pNorams, const D3DXVECTOR3 * pVertices, int verticesNum, const DWORD * pIndices, int indicesNum)
	{
		//�븻���� �ʱ�ȭ
		ZeroMemory(pNorams, sizeof(D3DXVECTOR3) * verticesNum);

		//�ﰢ�� ����
		DWORD triNum = indicesNum / 3;
		for (DWORD i = 0; i < triNum; i++)
		{
			//�ش� �ﰢ���� ���� �ε���
			DWORD i0 = pIndices[(i * 3) + 0];
			DWORD i1 = pIndices[(i * 3) + 1];
			DWORD i2 = pIndices[(i * 3) + 2];

			//���� 3��
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

			//���� ��Ų��.
			pNorams[i0] += normal;
			pNorams[i1] += normal;
			pNorams[i2] += normal;
		}

		//���� ������ Normalvector ����ȭ�Ѵ�.
		for (DWORD i = 0; i < verticesNum; i++)
		{
			D3DXVec3Normalize(&pNorams[i], &pNorams[i]);
		}
	}

	//ź��Ʈ�� ���̳븻 ���
	void ComputeTangentBinormal(D3DXVECTOR3 * outTangets, D3DXVECTOR3 * outBinormals, const D3DXVECTOR3 * pPositions, const D3DXVECTOR3 * pNormals, const D3DXVECTOR2 * pUVs, const DWORD * pIndices, DWORD NumTris, DWORD NumVertices)
	{
		//ź��Ʈ ���̳븻 �ʱ�ȭ
		ZeroMemory(outTangets, sizeof(D3DXVECTOR3) * NumVertices);
		ZeroMemory(outBinormals, sizeof(D3DXVECTOR3) * NumVertices);

		//�ӽ� Tangent Binormal �迭
		D3DXVECTOR3* pTangents = new D3DXVECTOR3[NumVertices];
		D3DXVECTOR3* pBinormals = new D3DXVECTOR3[NumVertices];

		//�ӽ� Tangent Binormal �迭 �ʱ�ȭ
		ZeroMemory(pTangents, sizeof(D3DXVECTOR3) * NumVertices);
		ZeroMemory(pBinormals, sizeof(D3DXVECTOR3) * NumVertices);

		//�ϴ� �ﰢ�� �����....
		for (DWORD a = 0; a < NumTris; a++)
		{
			//�ش� �ﰢ���� �ε���
			DWORD i0 = pIndices[a * 3 + 0];
			DWORD i1 = pIndices[a * 3 + 1];
			DWORD i2 = pIndices[a * 3 + 2];

			//�ش� �ﰢ���� ������ġ
			D3DXVECTOR3 p0 = pPositions[i0];
			D3DXVECTOR3 p1 = pPositions[i1];
			D3DXVECTOR3 p2 = pPositions[i2];

			//�ش� �ﰢ���� UV
			D3DXVECTOR2 uv0 = pUVs[i0];
			D3DXVECTOR2 uv1 = pUVs[i1];
			D3DXVECTOR2 uv2 = pUVs[i2];

			//������ Edge
			D3DXVECTOR3 edge1 = p1 - p0;
			D3DXVECTOR3 edge2 = p2 - p0;

			//UV Edge
			D3DXVECTOR2 uvEdge1 = uv1 - uv0;
			D3DXVECTOR2 uvEdge2 = uv2 - uv0;

			// ���� ������ ������ ���� ������ ����
			// edge1 = ( uvEdge1.x ) * Tangent + ( uvEdge1.y ) * Binormal;
			// edge2 = ( uvEdge2.x ) * Tangent + ( uvEdge2.y ) * Binormal;

			// ������ ���� ġȯ
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

			//ź��Ʈ ���̳븻 �ӽ� �迭�� �߰�
			pTangents[i0] += t;
			pTangents[i1] += t;
			pTangents[i2] += t;
			pBinormals[i0] += b;
			pBinormals[i1] += b;
			pBinormals[i2] += b;
		}

		//Binormal Tangent �븻�� ����ȭ
		for (int i = 0; i < NumVertices; i++) 
		{
			D3DXVECTOR3 n = pNormals[i];

			//Tangent �׶�����Ʈ ����
			D3DXVECTOR3 t = pTangents[i] - (D3DXVec3Dot(&pTangents[i], &n) * n);
			D3DXVec3Normalize(&t, &t);

			//�븻�� ����ȭ�� T �� �����Ͽ� B
			D3DXVECTOR3 b;
			D3DXVec3Cross(&b, &n, &t);
			D3DXVec3Normalize(&b, &b);

			outTangets[i] = t;
			outBinormals[i] = b;
		}

		//�ӽ� �迭 ����
		SAFE_DELETE_ARRAY(pTangents);
		SAFE_DELETE_ARRAY(pBinormals);
	}
	DWORD FloatToDWORD(float f)
	{
		float* pFloat = &f;

		DWORD* pDword = (DWORD*)pFloat;

		return *pDword;
	}
}