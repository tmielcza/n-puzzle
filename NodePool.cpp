#include "NodePool.hpp"

#include <iostream>

NodePool::~NodePool();

NodePool::NodePool(size_t size)
{
	this->size = size;
	this->allocateNodes(1000);
}

#include <iterator>

// Needs to free
void	NodePool::allocateNodes(size_t number)
{
	size_t	size = this->size;
	size_t	size2 = size * size;
	Node*	nodes = new Node[number];
	char**	pmaps = new char*[size * number];
	char*	maps = new char[size * size * number];

	for (size_t i = 0; i < number; i++)
	{
		nodes[i].size = size;
		nodes[i].map = pmaps + i * size;
		for (size_t j = 0; j < size; j++)
		{
			nodes[i].map[j] = maps + (i * size2) + j * size;
		}
		this->freeNodes.push(nodes + i);
	}
}

Node*	NodePool::newNode(void)
{
	Node*	tmp;

	if (this->freeNodes.empty())
	{
		this->allocateNodes(1000);
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
