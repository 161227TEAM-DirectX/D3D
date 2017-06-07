#pragma once

class light
{
public:
	dx::transform*	_transform;	//라이트 트랜스폼
	D3DXCOLOR	_color;		//라이트 컬러
	float		_intensity;	//라이트 강도

public:
	// 라이트 행렬
	// Pos.x,      Pos.y,      Pos.z,     lightType (0 Direction, 1 Point, 2 Spot)
	// Dir.x,      Dir.y,      Dir.z,     DistancePow;
	// Color.r,    Color.g,    Color.b,   strength
	// MaxRange,   MinRange,   InAngle    OutAngle 

	//라이트 행렬 얻기
	virtual D3DXMATRIXA16 getLightMatrix() = 0;
	//라이트 기즈모를 그린다.
	virtual void renderGizmo() = 0;

	light();
	~light();
};

