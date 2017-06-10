#include "stdafx.h"
#include "renderToTexture1.h"


HRESULT renderToTexture1::init(void)
{
	//���� �ִ� �޽����� ������ ���� ��ķ� ��������  ��� ������ Ʋ�������.
	D3DXMATRIXA16 matScale, matRotate, matCorrection;
	D3DXMatrixScaling(&matScale, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	matCorrection = matScale * matRotate;

	//���� �޽��ε�
	xMeshStatic* mesh = RM_XMESH->getResource("Resources/Meshes/Fighter/Fighter.x", &matCorrection);

	//����Ʈ �Է�
	lightDirection* pLight1 = new lightDirection;
	pLight1->_color = D3DXCOLOR(1, 1, 1, 1);
	pLight1->_intensity = 1.0f;
	//����Ʈ ���Ϳ� ���
	_lights.push_back(pLight1);


	//������Ʈ ����
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		for (int j = 0; j < OBJECT_NUM; j++)
		{
			baseObject* pNewObject = new baseObject();
			pNewObject->setMesh(mesh);
			pNewObject->setActive(true);
			//��ġ ����
			pNewObject->_transform->SetWorldPosition(i * 10, 0, j * 20);
			//���� ������Ʈ �Է�
			this->_renderObjects.push_back(pNewObject);
		}
	}

	//�߰� ī�޶�
	_extraCam = new camera();
	_extraCam->_camFar = 100.0f;

	int width = 512;
	int height = 512;

	//����Ʈ�� Cam ��Ⱦ��
	_extraCam->_aspect = (float)width / (float)height;

	//RenderTarget ��  texture �����
	_device->CreateTexture(
		width,						//�ؽ��� ���� �ػ�
		height,						//�ؽ��� ���� �ػ�
		1,							//�Ӹ�ü�� ����
		D3DUSAGE_RENDERTARGET,		//RenderTarget�� Texture
		D3DFMT_A8R8G8B8,			//�ؽ��� ����. RenderTexture �� D3DFMT_A8R8G8B8 �� ����
		D3DPOOL_DEFAULT,			//RecderTexture �� Texture �� Pool �� Default
		&_renderTexture,			//������ �ؽ��� �޾ƿ� ������
		NULL
	);

	//Render��  Surface
	_device->CreateDepthStencilSurface(
		width,						// texture �����ػ�
		height,						// texture �����ػ�
		D3DFMT_D24S8,				//Depth �� 24��Ʈ, Stencil �� 8��Ʈ
		D3DMULTISAMPLE_NONE,		//��Ƽ ���ø�. ��Ƽ�˸��ƽ��� �������� �ʴ´�.(������ ���� �ɸ�)
		0,							//��Ƽ ���ø� ����Ƽ�� 0
		TRUE,						//���� ��ü�� ���� ���۳����� �����ϴ�? ���ϴ�?(TRUE �� ���� ���۱�ü �ɶ� ������ ���� ���۳����� ������� �ʴ´�.)
		&_renderSurface,			//���� ������
		NULL						//�׳� ��
	);
	//�� ���� : ����, ���� ũ��� ���������� ����� �ؽ��ĳ� ǥ���� ũ��,
	//�������İ� �ݵ�� ��ġ�ؾ� �Ѵ�.�׷��� ������ ����� �� ����.

	return S_OK;
}

void renderToTexture1::release(void)
{
	//����Ʈ ����
	for (int i = 0; i < this->_lights.size(); i++)
	{
		SAFE_DELETE(this->_lights[i]);
	}
	//������Ʈ ����
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		SAFE_DELETE(this->_renderObjects[i]);
	}
	//�߰�ī�޶� ����
	SAFE_DELETE(this->_extraCam);
}

void renderToTexture1::update(void)
{
	//�߰� ī�޶� ��Ʈ��
	this->_extraCam->DefaultMyControl(_timeDelta);
	this->_extraCam->updateMatrix();
	this->_extraCam->updateFrustum();


	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_mainCamera->updateFrustum();
	}

	this->_cullObjects.clear();
	for (int i = 0; i < this->_renderObjects.size(); i++) 
	{
		this->_renderObjects[i]->update();

		//�������� �ȿ� �ִ�?
		if (_mainCamera->_frustum.isInFrustum(this->_renderObjects[i]))
		{
			this->_cullObjects.push_back(this->_renderObjects[i]);
		}
	}
}

void renderToTexture1::render(void)
{
	//ȭ�鿡 ������ �Ǵ� ��� Texture�� �������Ѵ�.

	//�� ����̽��� Target ������ǥ��� DepthStencil ������ ǥ�������� ���
	LPDIRECT3DSURFACE9		pDeviceTargetSurface;
	LPDIRECT3DSURFACE9		pDeviceDepthAndStencilSurface;
	_device->GetRenderTarget(0, &pDeviceTargetSurface);
	_device->GetDepthStencilSurface(&pDeviceDepthAndStencilSurface);

	//RenderTexture �� Surface �� ��´�.
	LPDIRECT3DSURFACE9 texSurface = NULL;
	if (SUCCEEDED(this->_renderTexture->GetSurfaceLevel(0, &texSurface)))
	{
		//Texture ǥ���� Device �� Target ���۷� �����Ѵ�.
		_device->SetRenderTarget(0, texSurface);

		//���õ� Surface ������ �ٷ� �����ִ� ���Ǹ� ������...
		SAFE_RELEASE(texSurface);
	}

	//Depth ���ۿ� Stencil ������ Surface�� _renderSurface ����
	_device->SetDepthStencilSurface(_renderSurface);

	//����̽� ���� Ŭ���� (��� ������ Setting�� Textuer�� Surface�� Ŭ���� �ȴ�)
	_device->Clear(0, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		0xffffff00,							//���� ������ �ȵ� �κ��� ����
		1.0f,								//�׸� Z ���� ����(1�� ��������)
		0);


	xMeshStatic::setCamera(this->_extraCam);
	xMeshStatic::setLighting(&this->_lights);

	for (int i = 0; i < this->_cullObjects.size(); i++)
	{
		this->_cullObjects[i]->render();
	}

	//Render Texture �� �׸� �۾��� �������� �ٽ� ���󺹱��ϴ� ����....
	_device->SetRenderTarget(0, pDeviceTargetSurface);
	_device->SetDepthStencilSurface(pDeviceDepthAndStencilSurface);

	//���õ� Surface ������ �ٷ� �����ִ� ���Ǹ� ������...
	SAFE_RELEASE(pDeviceTargetSurface);
	SAFE_RELEASE(pDeviceDepthAndStencilSurface);

	xMeshStatic::setCamera(this->_mainCamera);
	xMeshStatic::setLighting(&this->_lights);

	for (int i = 0; i < this->_cullObjects.size(); i++)
	{
		this->_cullObjects[i]->render();
	}
	//�������� �׷�����
	this->_mainCamera->_frustum.renderGizmo();
	//Extra ī�޶� ��������
	this->_extraCam->_frustum.renderGizmo();
}

void renderToTexture1::renderSprite(void)
{
	RECT rcSour = { 0, 0, 256, 256 };
	RECT rcDest = { 0, 0, 256, 256 };
	SPRITEMANAGER->renderArea(_renderTexture, &rcSour, &rcDest);
}
