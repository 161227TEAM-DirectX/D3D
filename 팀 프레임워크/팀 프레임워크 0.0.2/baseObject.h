#pragma once

class baseObject
{
public:
	xMesh*				_mesh;					//���� ����� �޽�
	dx::transform*			_transform;				//Ʈ������
	boundBox			_boundBox;				//�浹�ڽ�
	bool				_ignoreCreateShadow;	//������� ���鶧 ���õǳ�?

protected:
	bool				_isActive;				//Ȱ��ȭ ����
	skinnedAnimation*	_skinnedAnim;			//��Ų�� �ִϸ��̼�

protected:
	//override�� �ʿ��ϸ� ������ �ؼ� ����ϱ�
	virtual void baseObjectEnable() {}			//BaseObject�� Ȱ��ȭ �ɶ� ����
	virtual void baseObjectDisable() {}			//BaseObject�� ��Ȱ��ȭ �ɶ� ����
	virtual void baseObjectUpdate() {}			//BaseObject�� Update �� ����
	virtual void baseObjectNoActiveUpdate() {}	//BaseObject�� ��Ȱ��ȭ�� ������Ʈ ����
	virtual void baseObjectRender();			//BaseObject�� �׸��� ����

public:
	void update();
	void render();

	//������ �� �޽��� �����Ѵ�.
	void setMesh(xMesh*	pMesh);
	//Ȱ��ȭ ����
	void setActive(bool isActive);
	//Ȱ��ȭ ���θ� ��´�.
	bool getActive() { return _isActive; }

	//���õ� �޽��� ���� �ٿ��ڽ��� ���� �Ѵ�.
	void computeBoundBox();

	baseObject();
	~baseObject();
};

