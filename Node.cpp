#include <iostream>
#include <cstring>
#include <algorithm>
#include "Node.hpp"

void	Node::setMap(const char * const * map) {
	std::copy(map[0], map[0] + this->size * this->size, this->map[0]);
}

Node::Node(void) {}

Node::~Node(void) {}


Node::Node(size_t size) : size(size) {
	this->map = new char*[size];
	this->map[0] = new char[size * size];
	for (size_t i = 1; i < size; i++)
		this->map[i] = this->map[0] + size * i;
}

Node::Node(const char * const * map, int size)
	: Node(size)
{
	this->setMap(map);
	this->hash();
	Node::Square sq = find0(map, size);
	this->pos0.x = sq.x;
	this->pos0.y = sq.y;
	this->cost = 0;
	this->heuristic = 0;
	this->distance = 0;
	this->parent = NULL;
}

Node::Node(const char * const * map, int size, int cost, int heuristic, char pos0[2], Node *parent)
	: size(size),
	  cost(cost),
	  heuristic(heuristic),
	  parent(parent),
	  pos0 {pos0[0], pos0[1]}
{
	this->distance = cost + heuristic;
	this->map = new char*[this->size];
	for (size_t i = 0; i < this->size; i++)
	{
		this->map[i] = new char[this->size];
	}
	this->setMap(map);
	this->hash();
}

Node::Node(const Node& src) : Node(src.size) {
	*this = src;
}

Node::Square	Node::find0(const char * const * map, size_t size) {
	Square pos0;

	for (unsigned int x = 0; x < size; x++)
	{
		for (unsigned int y = 0; y < size; y++)
		{
			if (map[y][x] == 0)
			{
				pos0.x = x;
				pos0.y = y;
				break;
			}
		}
	}
	return (pos0);
}

void	Node::dump(void) const
{
	for (size_t y = 0; y < this->size; y++)
	{
		for (size_t x = 0; x < this->size; x++)
		{
			if ((int)x == this->pos0.x && (int)y == this->pos0.y)
				std::cout << "\e[38;5;163m" << (int)this->map[y][x] << "\033\[0m ";
			else
				std::cout << (int)this->map[y][x] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "f(x): " << this->distance << std::endl;
	std::cout << "h(x): " << this->heuristic << std::endl;
}

char*	Node::square(const Square& s) const {
	return (&this->map[s.y][s.x]);
}

Node&	Node::operator=(const Node& rhs) {
	this->size = rhs.size;
	setMap(rhs.map);
	this->_hash = rhs._hash;
	this->pos0.x = rhs.pos0.x;
	this->pos0.y = rhs.pos0.y;
	this->cost = rhs.cost;
	return (*this);
}

bool	operator==(const Node& lhs, const Node& rhs) {
	if (lhs._hash != rhs._hash)
		return (false);
	return std::equal(lhs.map[0], lhs.map[0] + lhs.size * lhs.size, rhs.map[0]);
}

bool	operator<(const Node& lhs, const Node& rhs) {
	return (lhs.size < rhs.size);
}

Node::Square	operator+(Node::Square lhs, const Node::Square& rhs) {
	Node::Square tmp(lhs.x + rhs.x, lhs.y + rhs.y);
	return (tmp);
}

void	Node::hash(void)
{
	size_t	hash = 0;
	size_t	i = 0;

	for (size_t y = 0; y < this->size; y++)
	{
		for (size_t x = 0; x < this->size; x++, i++)
		{
			hash ^= ((size_t)(this->map[y][x] & 0xF) << ((i & 7) << 2));
		}
	}
	this->_hash = hash;
}
