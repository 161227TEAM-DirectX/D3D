#include "stdafx.h"
#include "dxEmitter.h"

void dxEmitter::release()
{
	 _module->relese();
	 SAFE_DELETE(_module);
}
