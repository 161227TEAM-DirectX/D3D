#pragma once

class baseObject;

class frustum
{
private:
	D3DXVECTOR3		_RHWPos[8];		//viewProjection 변환전 위치
	D3DXVECTOR3		_pos[8];		//변환 후 위치
	D3DXPLANE		_plane[6];		//절두체 평면

public:
	frustum();
	~frustum();

	//프러스텀 정보 업데이트 ( View * Projection 행렬을 요구한다 )
	void updateFrustum(D3DXMATRIXA16* pmatViewProj);

	//Base 오브젝트가 프러스텀 안에있는지 체크
	bool isInFrustum(baseObject* pObject);

	//프러스텀 기즈모를 그린다.
	void renderGizmo();
};

