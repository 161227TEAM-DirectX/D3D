#pragma once

class baseObject;

class frustum
{
private:
	D3DXVECTOR3		_RHWPos[8];		//viewProjection ��ȯ�� ��ġ
	D3DXVECTOR3		_pos[8];		//��ȯ �� ��ġ
	D3DXPLANE		_plane[6];		//����ü ���

public:
	frustum();
	~frustum();

	//�������� ���� ������Ʈ ( View * Projection ����� �䱸�Ѵ� )
	void updateFrustum(D3DXMATRIXA16* pmatViewProj);

	//Base ������Ʈ�� �������� �ȿ��ִ��� üũ
	bool isInFrustum(baseObject* pObject);

	//�������� ����� �׸���.
	void renderGizmo();
};

