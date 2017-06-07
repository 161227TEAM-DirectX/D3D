#include "stdafx.h"
#include "light.h"

light::light() : _intensity(1.0f)
{
	_transform = new dx::transform;
}

light::~light()
{
	SAFE_DELETE(_transform);
}
