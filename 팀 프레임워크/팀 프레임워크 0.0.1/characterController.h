#pragma once
class characterController
{
protected:
	D3DXMATRIXA16 _matWorld;

	D3DXVECTOR3		_vCubePos;
	D3DXVECTOR3		_vDir;
	float			_angle;
	float			_speed;

public:
	HRESULT init(void);
	void release(void);//�ʿ����
	void update(void);
	void render(void);//�ʿ����

	D3DXMATRIXA16* GetWorldTM() { return &_matWorld; }
	D3DXVECTOR3* GetPosition() { return &_vCubePos; }

	characterController() {}
	~characterController() {}
};

