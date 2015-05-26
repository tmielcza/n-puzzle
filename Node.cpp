#include "Node.hpp"

void	Node::setMap(const char * const * map) {
	for (size_t x = 0; x < this->size; x++)
	{
		for (size_t y = 0; y < this->size; y++)
		{
			this->map[y][x] = map[y][x];
		}
	}
}

Node::Node(void) {}

Node::Node(size_t size) : size(size)
{
	this->map = new char*[size];
	for (size_t i = 0; i < size; i++)
	{
		this->map[i] = new char[size];
	}
}

Node::Node(const char * const * map, int size, int cost, int heuristic, char pos0[2], Node *parent)
	: size(size),
	  cost(cost),
	  heuristic(heuristic),
	  parent(parent),
	  pos0 {pos0[0], pos0[1]}
{
	this->map = new char*[this->size];
	for (size_t i = 0; i < this->size; i++)
	{
		this->map[i] = new char[this->size];
	}
	this->setMap(map);
}

Node::Node(const Node& src) : Node(src.size) {
	*this = src;
}

Node&	Node::operator=(const Node& rhs) {
	this->size = rhs.size;
	setMap(rhs.map);
	this->pos0[0] = rhs.pos0[0];
	this->pos0[1] = rhs.pos0[1];
	this->cost = rhs.cost;
	return (*this);
}

#include <cstring>

bool	operator==(const Node& lhs, const Node& rhs) {
	for (size_t i = 0; i < lhs.size; i++)
	{
		if (memcmp(lhs.map[i], rhs.map[i], lhs.size))
		{
			return (false);
		}
	}
	return (true);
}

bool	operator<(const Node& lhs, const Node& rhs) {
	return (lhs.size < rhs.size);
}
