#include "stdafx.h"
#include "Tportal.h"

HRESULT Tportal::init(void)
{
	return S_OK;
}

void Tportal::release(void)
{
}

void Tportal::render()
{
}


void Tportal::portalSet(dx::transform* inTrans)
{
	D3DXVECTOR3 center = inTrans->GetWorldPosition();

	_trans = inTrans;

	//���� ����� ����
	_rgb.a = 0.6f;
	_rgb.b = 0.0f;
	_rgb.r = 0.4f;
	_rgb.b = 0.8f;
	_rgb.start = false;
	_rgb.aBool = true;
	_rgb.bBool = true;
	_rgb.gBool = true;
	_rgb.rBool = true;


	_doorBump = NULL;
	_doorEffect = NULL;
	_doorCube = NULL;
	_doorVertexBuffer = NULL;
	_doorTime = 0.0f;

	D3DXVECTOR3 y[6];
	y[0] = D3DXVECTOR3(0.0f, 11.0f, 0.0f);
	y[1] = D3DXVECTOR3(0.0f, 11.0f, 0.0f);
	y[2] = D3DXVECTOR3(0.0f, 6.0f, 0.0f);
	y[3] = D3DXVECTOR3(0.0f, 6.0f, 0.0f);
	y[4] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	y[5] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 x = inTrans->GetRight();

	_doorVertex[0].xyz = center + (-x * 3.0f) + y[0];
	_doorVertex[1].xyz = center + (+x * 3.0f) + y[1];
	_doorVertex[2].xyz = center + (-x * 5.7f) + y[2];
	_doorVertex[3].xyz = center + (+x * 5.7f) + y[3];
	_doorVertex[4].xyz = center + (-x * 5.0f) + y[4];
	_doorVertex[5].xyz = center + (+x * 3.0f) + y[5];

	for (int i = 0; i < 6; i++)
	{
		_doorVertex[i].color = D3DCOLOR_XRGB(0, 0, 0);
	}

	_device->CreateVertexBuffer(6 * sizeof(DoorVertex), D3DUSAGE_WRITEONLY, DoorVertex::FVF_Flags, D3DPOOL_DEFAULT, &_doorVertexBuffer, NULL);

	void *pVertices = NULL;

	_doorVertexBuffer->Lock(0, sizeof(_doorVertex), (void**)&pVertices, 0);
	memcpy(pVertices, _doorVertex, sizeof(_doorVertex));
	_doorVertexBuffer->Unlock();

	D3DXCreateTextureFromFile(_device, "terrain6.png", &_doorBump);
	D3DXCreateCubeTextureFromFile(_device, "cubemap.dds", &_doorCube);

	HRESULT HR;
	LPD3DXBUFFER pBufferErrors = NULL;

	HR = D3DXCreateEffectFromFile(_device,
		"water.fx",
		NULL,
		NULL,
		D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY,
		NULL,
		&_doorEffect,
		&pBufferErrors);

	_eye = D3DXVECTOR4(center.x, center.y + 5.5f, center.z, 1.0f);
}

void Tportal::update()
{
	if (_rgb.aBool == true)
	{
		if (_rgb.a >= 0.3f)
		{
			_rgb.start = true;
		}
		if (_rgb.start == true)
		{
			if (_rgb.bBool == false) _rgb.b -= 0.005f;
			if (_rgb.gBool == false) _rgb.g -= 0.005f;
			if (_rgb.rBool == false) _rgb.r -= 0.005f;
		}
		if (_rgb.bBool == true) _rgb.b += 0.005f;
		if (_rgb.gBool == true) _rgb.g += 0.005f;
		if (_rgb.rBool == true) _rgb.r += 0.005f;

		if (_rgb.r >= 1.0f) _rgb.rBool = false;
		else if (_rgb.r <= 0.0f) _rgb.rBool = true;

		if (_rgb.g >= 1.0f) _rgb.gBool = false;
		else if (_rgb.g <= 0.0f) _rgb.gBool = true;

		if (_rgb.b >= 1.0f) _rgb.bBool = false;
		else if (_rgb.b <= 0.0f) _rgb.bBool = true;
	}

	_doorShader.AlphaLayer = true;                                    //���� ���̾�
	_doorShader.BumpScale = 0.2f;                                      //���� ������
	_doorShader.bumpSpeed = D3DXVECTOR2(0, 0);
	_doorShader.deepColor = D3DXVECTOR4(0.0f, 0.3f, 0.5f, 0.9f);     //�ָ��������� ���������ε�
	_doorShader.fresnelBias = 0.328f; //���� �� ���̾
	_doorShader.fresnelPower = 1.0f;   //���� �� �Ŀ�
	_doorShader.hdrMultiplier = 0.471f; //hdr ������
	_doorShader.reflectionAmount = 1.0f; //�������� ���� ����� // �ݻ� ��
	_doorShader.reflectionBlur = 0.0f; //�ݻ� �帲
	_doorShader.reflectionColor = D3DXVECTOR4(_rgb.r, _rgb.g, _rgb.b, _rgb.a); //�ݻ����
	_doorShader.shallowColor = D3DXVECTOR4(0, 1, 1, 1.0f);    //��������(�ٷθ��� ����)
	_doorShader.textureScale = D3DXVECTOR2(1, 2); //�ؽ��ĸ� �����ʼ� �ϴ°�
	_doorShader.waterAmount = 0.01f;                  //�ٴ��� ����� �Ķ��� ����°� ����
	_doorShader.waveAmp = 0.05f;                      //���̺� ���� // ���� �Ӵٰ����ϰ� �ϴ°Ű���
	_doorShader.waveFreq = 2.2f;                     //�� ���ļ� //��Ȯ���𸣰���
	_doorShader._using = true;

	_doorTime += 0.05f;
}

void Tportal::renderPortal()
{

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	//���ʺκп� ���߿� ī�޶� ��ġ
	//��Ż ������ �������ؼ� �̷������� ����
	_doorEffect->SetTexture("texture0", _doorBump);
	_doorEffect->SetTexture("texture1", _doorCube);
	_doorEffect->SetMatrix("WorldViewProj", &_camera->getViewProjectionMatrix());
	_doorEffect->SetVector("eyePosition", &_eye);
	_doorEffect->SetFloat("time", _doorTime);
	_doorEffect->SetValue("textureScale", _doorShader.textureScale, sizeof(D3DXVECTOR2));
	_doorEffect->SetFloat("waveFreq", _doorShader.waveFreq);
	_doorEffect->SetFloat("waveAmp", _doorShader.waveAmp);
	_doorEffect->SetFloat("BumpScale", _doorShader.BumpScale);
	_doorEffect->SetValue("bumpSpeed", _doorShader.bumpSpeed, sizeof(D3DXVECTOR2));
	_doorEffect->SetVector("deepColor", &_doorShader.deepColor);
	_doorEffect->SetVector("shallowColor", &_doorShader.shallowColor);
	_doorEffect->SetFloat("waterAmount", _doorShader.waterAmount);
	_doorEffect->SetVector("reflectionColor", &_doorShader.reflectionColor);
	_doorEffect->SetFloat("reflectionAmount", _doorShader.reflectionAmount);
	_doorEffect->SetFloat("reflectionBlur", _doorShader.reflectionBlur);
	_doorEffect->SetFloat("fresnelPower", _doorShader.fresnelPower);
	_doorEffect->SetFloat("fresnelBias", _doorShader.fresnelBias);
	_doorEffect->SetFloat("hdrMultiplier", _doorShader.hdrMultiplier);
	_doorEffect->SetTechnique("water");

	DWORD alpha = 175;
	_device->SetRenderState(D3DRS_TEXTUREFACTOR, (0x00ffffff) + (alpha << 24));
	_device->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

	// ���� ä���� �־ �������ϰ� ����.
	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);





	UINT uPasses;
	_doorEffect->Begin(&uPasses, 0);

	for (UINT uPass = 0; uPass < uPasses; ++uPass)
	{
		_doorEffect->BeginPass(uPass);
		_device->SetStreamSource(0, _doorVertexBuffer, 0, sizeof(DoorVertex));
		_device->SetFVF(DoorVertex::FVF_Flags);
		_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 4);

		_doorEffect->EndPass();
	}

	_doorEffect->End();

	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

