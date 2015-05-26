#include "NodePool.hpp"

		NodePool::NodePool(size_t size)
{
//	this->allocateNodes(1000);
	this->size = size;
}

void	NodePool::allocateNodes(size_t number)
{
	Node*	nodes = new Node[number];
	char**	pmaps = new char*[sizeof(char) * this->size];
	char*	maps = new char[sizeof(char) * this->size * this->size];

	for (size_t i = 0; i < number; i++)
	{
		nodes[i].map = pmaps + i * this->size;
		for (size_t j = 0; j < this->size; j++)
		{
			nodes[i].map[j] = maps + (i * this->size) + j;
		}
		this->freeNodes.push(nodes + i);
	}
}

Node*	NodePool::newNode(void)
{
	Node*	tmp;

	if (this->freeNodes.empty())
	{
		this->allocateNodes(1);
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
