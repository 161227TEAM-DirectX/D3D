#include "stdafx.h"
#include "treeNode.h"

void treeNode::addChild(treeNode * child)
{
	if (_child == NULL)
	{
		_child = child;
	}
	else
	{
		_child->addSibling(child);
	}
}

void treeNode::addSibling(treeNode * sibling)
{
	if (_sibling)
	{
		_sibling->addSibling(sibling);
	}
	else
	{
		_sibling = sibling;
	}
}

void treeNode::destroy()
{
	if (_child)
	{
		_child->destroy();
	}
	if (_sibling)
	{
		_sibling->destroy();
	}

	delete this;
}
