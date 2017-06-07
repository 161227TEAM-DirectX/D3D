#pragma once

class treeNode
{
protected:
	treeNode* _child;
	treeNode* _sibling;

public:
	virtual void addChild(treeNode* child);
	virtual void addSibling(treeNode* sibling);
	virtual void destroy();

	treeNode() : _child(NULL), _sibling(NULL) {}
	virtual ~treeNode() {}
};

