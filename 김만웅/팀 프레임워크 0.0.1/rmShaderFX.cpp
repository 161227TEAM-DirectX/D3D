#include "stdafx.h"
#include "rmShaderFX.h"

HRESULT rmShaderFX::init(void)
{
	return S_OK;
}

void rmShaderFX::release(void)
{
}

LPD3DXEFFECT rmShaderFX::loadResource(string filePath, void * pParam)
{
	LPD3DXEFFECT	effect = NULL; //���̴� ����Ʈ ����

	//���̴� �ε�
	//���̴� �ε��� ������ ������ ���� ������ ������ �޾ƿ� Error����
	LPD3DXBUFFER	error = NULL;
	DWORD			shaderFlag = 0;

#ifdef _DEBUG
	//���̴��� ����׸��� �������ϰڴ� (����׸��� �ؾ� �߸��� ������ ������ ���� Error ���ۿ� ���������� ����) 
	shaderFlag = shaderFlag | D3DXSHADER_DEBUG;
#endif

	//fxFile �� ���� Effect ��ü �ε�
	D3DXCreateEffectFromFile(
		_device,			//����̽�
		filePath.c_str(),	//�ҷ��� ���̴� �ڵ� �����̸�
		NULL, 				//���̴��� �������Ҷ� �߰��� ����� #define ���� ( �ϴ� NULL )
		NULL, 				//���̴��� �������Ҷ� #include ���ù��� ó���Ҷ� ����� �������̽� �÷��� ( �ϴ� NULL )
		shaderFlag,			//���̴� ������ �÷���
		NULL, 				//���̴� �Ű������� ������ �޸�Ǯ ( �ϴ� NULL )
		&effect,			//�ε��� ���̴� Effect ������
		&error 				//���̴��� �ε��ϰ� �������Ҷ� ������ ����� �ش� ���ۿ� �����޽����� ���� ( ���������� �ε��Ǹ� NULL �� �����ȴ� )
	);

	//�ε��� ������ �ִٸ�....
	if (error != NULL && effect == NULL)
	{
		//Error ���� Release
		SAFE_RELEASE(error);
		return NULL;
	}
	return effect;
}

void rmShaderFX::releaseResource(LPD3DXEFFECT data)
{
	SAFE_RELEASE(data);
}
