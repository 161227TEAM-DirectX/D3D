#include "stdafx.h"
#include "boundObject.h"

void boundObject::baseObjectUpdate()
{
	this->_transform->DefaultMyControl(_timeDelta);

	if (KEYMANAGER->isStayKeyDown('T'))
	{
		_halfSize.z += _timeDelta;
	}

	else if (KEYMANAGER->isStayKeyDown('G'))
	{
		_halfSize.z -= _timeDelta;
		if (_halfSize.z < 0.0f) _halfSize.z = 0.0f;
	}

	if (KEYMANAGER->isStayKeyDown('F'))
	{
		_halfSize.x += _timeDelta;
	}

	else if (KEYMANAGER->isStayKeyDown('H'))
	{
		_halfSize.x -= _timeDelta;
		if (_halfSize.x < 0.0f) _halfSize.x = 0.0f;
	}

	if (KEYMANAGER->isStayKeyDown('U'))
	{
		_halfSize.y += _timeDelta;
	}

	else if (KEYMANAGER->isStayKeyDown('J'))
	{
		_halfSize.y -= _timeDelta;
		if (_halfSize.y < 0.0f) _halfSize.y = 0.0f;
	}

	this->_boundBox.setBound(&_center, &_halfSize);
}
