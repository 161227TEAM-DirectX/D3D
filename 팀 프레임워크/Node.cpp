#include "stdafx.h"
#include "Node.h"

Node::Node()
	:position(0, 0, 0), via(-1), cost(0), visited(false), mesh(nullptr)
{
}

Node::Node(int selfIndex, float cost, int via, Node& temp)
	: selfIndex(selfIndex), cost(cost), via(via), position(temp.position), visited(temp.visited), 
	radius(temp.radius)
{
	this->setMesh(radius);
}


Node::~Node()
{
	SAFE_RELEASE(mesh);
}

void Node::Render()
{
	if (KEYMANAGER->isToggleKey('O'))
	{
		D3DXMATRIXA16 matT;
		D3DXMATRIX oldMat;
		D3DXMatrixTranslation(&matT,
			position.x,
			position.y,
			position.z);
		_device->GetTransform(D3DTS_WORLD, &oldMat);
		_device->SetTransform(D3DTS_WORLD, &matT);
		_device->SetFVF(mesh->GetFVF());
		mesh->DrawSubset(0);
		_device->SetTransform(D3DTS_WORLD, &oldMat);
	}
}
