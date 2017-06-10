#include "stdafx.h"
#include "_1pointPaticle.h"

HRESULT _1pointPaticle::init(void)
{
	//����ī�޶� ��ġ ����
	_mainCamera->SetWorldPosition(0, 1, -5);

	//���� ��ġ
	_particleVertex[0].pos = D3DXVECTOR3(-3, 0, 0);
	_particleVertex[1].pos = D3DXVECTOR3(0, 0, 0);
	_particleVertex[2].pos = D3DXVECTOR3(3, 0, 0);

	//���� ������
	_particleVertex[0].size = 2.0f;
	_particleVertex[1].size = 2.0f;
	_particleVertex[2].size = 2.0f;

	//���� �÷�
	_particleVertex[0].color = 0xffff0000;
	_particleVertex[1].color = 0xff00ff00;
	_particleVertex[2].color = 0xff0000ff;

	//������ ���� �ؽ��� ��������
	_texture = RM_TEXTURE->getResource("Resources/Textures/particle_0.png");

	return S_OK;
}

void _1pointPaticle::release(void)
{
}

void _1pointPaticle::update(void)
{
}

void _1pointPaticle::render(void)
{
	_device->SetRenderState(D3DRS_LIGHTING, false);						//�������� ����
	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);				//����Ʈ ��������Ʈ Ȱ��ȭ
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, true);				//����Ʈ�� ������ ���� ���̰ڴ�. FVF �� D3DFVF_PSIZE �ִ°��
	_device->SetRenderState(D3DRS_POINTSIZE_MIN, FloatToDWORD(0.0f));	//����Ʈ�� �ּ� ũ��(ȭ�����)
	_device->SetRenderState(D3DRS_POINTSIZE_MAX, FloatToDWORD(500.0f));	//����Ʈ�� �ִ� ũ��(ȭ�����)

	//��µǴ� POINT size 
	//finalSize = viewportHeight * pointSize *  sqrt( 1 / ( A + B(D) + C(D^2) )  );
	//�Ʒ��� ���� �ϸ� �ڿ������� �Ÿ��� ���� �������� ��Ÿ��
	_device->SetRenderState(D3DRS_POINTSCALE_A, FloatToDWORD(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_B, FloatToDWORD(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_C, FloatToDWORD(1.0f));

	//Texture �� ���� Diffuse ���⼭�� �����÷��� ���İ� �� ���� ���� ����� �Ѵ�.
	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

/////////////////////////////////////////////////////////////////////////////////
	//���� ���� ���� 
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	////1.������ ���� ���ĺ��� �ɼ��� �Ϲ� ���� ���ĺ��� ( ���ļ����� �ʿ��Ҽ� �ִ� )
	//_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//2.������ ���� ���ĺ��� �ɼ��� ���� �¿�� ( �� ȭ�� ������ ������ ǥ�� ) ( ���ļ����� �ʿ� ���� )
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	_device->SetRenderState(D3DRS_ZWRITEENABLE, false);	//z ������ ���⸦ ���´�.

///////////////////////////////////////////////////////////////////////////////////

	//��ƼŬ Texture ����
	_device->SetTexture(0, _texture);

	//��ƼŬ ���� ���
	_device->SetFVF(PARTICLE_VERTEX::FVF);

	//���������� �ʰ� �ٷ� �׸��� ( ���ֿ����̴� ������ ���� �������ϰ� ���� )
	_device->DrawPrimitiveUP(
		D3DPT_POINTLIST,		//PT
		3,						//�׸����� ���� 3����
		_particleVertex,		//VERTEX �迭 
		sizeof(PARTICLE_VERTEX)	//VERTEX �ϳ� Size 
	);

	//�ٽ� ������
	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	_device->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
