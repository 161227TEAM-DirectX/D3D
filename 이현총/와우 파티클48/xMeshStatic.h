#pragma once
#include "xMesh.h"

class xMeshStatic : public xMesh
{
public:
	static LPD3DXEFFECT				_staticMeshEffect;	//�����޽ø� �׸��� ����Ʈ
	static LPDIRECT3DTEXTURE9		_defDiffuseTex;		
	static LPDIRECT3DTEXTURE9		_defNormalTex;
	static LPDIRECT3DTEXTURE9		_defSpecularTex;
	static LPDIRECT3DTEXTURE9		_defEmissionTex;

public:
	LPD3DXMESH						_mesh;

	DWORD							_materialsNum;		//�ε��� �Ž��� ���� ����
	vector<LPDIRECT3DTEXTURE9>		_vecDiffuseTex;		//�ε��� �޽����� ����ϴ� DiffuseTexture
	vector<LPDIRECT3DTEXTURE9>		_vecNormalTex;		//�ε��� �޽����� ����ϴ� NormalTexture
	vector<LPDIRECT3DTEXTURE9>		_vecSpecularTex;	//�ε��� �޽����� ����ϴ� SpecularTexture
	vector<LPDIRECT3DTEXTURE9>		_vecEmissionTex;	//�ε��� �޽����� ����ϴ� EmissionTexture
	vector<D3DMATERIAL9>			_vecMaterials;		//�ε��� �޽����� ����ϴ� ���͸���

	vector<D3DXVECTOR3>				_vertices;			//������
	vector<D3DXVECTOR3>				_normals;			//�����븻
	vector<DWORD>					_indices;			//�ε���
	DWORD							_triNum;			//�ﰢ���� ����

public:
	D3DXVECTOR3						_boundMin;			//�ٿ���� �ּ� ��ġ 
	D3DXVECTOR3						_boundMax;			//�ٿ���� �ִ� ��ġ 
	D3DXVECTOR3						_boundCenter;		//�ٿ���� ���� (���ǻ��� �Ǻ��� �ƴϴ�)
	D3DXVECTOR3						_boundSize;			//�ٿ���� ũ��
	D3DXVECTOR3						_boundHalfSize;		//�ٿ���� ����ũ��
	float							_boundRadius;		//�ٿ���� ������ ������

	//�����Ŵ����� ��ģ��
	friend class physicManager;
public:
	xMeshStatic();
	~xMeshStatic();

	virtual HRESULT init(string filePath, D3DXMATRIXA16* matCorrection = NULL);
	virtual void release(void);
	virtual void render(transform* trans);

	//ī�޶� �����ϱ�
	static void setCamera(camera* camera);

	//���̽� ������ ���� ( ���̽� �������� ���⼺ �����̴� )
	static void setBaseLight(lightDirection* pDirLight);
	//������ ����
	static void setLighting(light** pLights, int lightNum);
	static void setLighting(vector<light*>* pLights);

	//technique ����
	static void setTechniqueName(string name);

private:
	//������Ĵ�� �޽��� �����Ѵ�
	void meshCorrection(D3DXMATRIXA16* matCorrection);
};

