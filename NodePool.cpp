#include "NodePool.hpp"

#include <iostream>

		NodePool::NodePool(size_t size)
{
	this->size = size;
	this->allocateNodes(10000);
}


// Needs to free
void	NodePool::allocateNodes(size_t number)
{
	Node*	nodes = new Node[number];
	char**	pmaps = new char*[this->size * number];
	char*	maps = new char[this->size * this->size * number];

	for (size_t i = 0; i < number; i++)
	{
		nodes[i].size = this->size;
		nodes[i].map = pmaps + i * this->size;
		for (size_t j = 0; j < this->size; j++)
		{
			nodes[i].map[j] = maps + (i * this->size * this->size) + j * this->size;
		}
		this->freeNodes.push(nodes + i);
	}
}

Node*	NodePool::newNode(void)
{
	Node*	tmp;

	if (this->freeNodes.empty())
	{
		this->allocateNodes(10000);
	}
	tmp = this->freeNodes.top();
	this->freeNodes.pop();
	return (tmp);
}

void	NodePool::delNode(Node* node)
{
	this->freeNodes.push(node);
}

NodePool::~NodePool(void)
{
}
