#include <queue>
#include <unordered_set>
#include <list>
#include "AStarSolver.hpp"
#include "Node.hpp"
#include "NodePool.hpp"
#include "Manhattan.hpp"

AStarSolver::~AStarSolver() {}

size_t	AStarSolver::hash_node(const Node* node) {
	return (node->_hash);
}

bool	AStarSolver::eq_node(const Node* a, const Node* b) {
	return (*a == *b);
}

bool	AStarSolver::less_node(const Node* a, const Node* b) {
	if (a->distance == b->distance)
		return (a->cost < b->cost);
	return (a->distance > b->distance);
}

std::list<Node*>	AStarSolver::buildPath(void)
{
	std::list<Node*>	lst;
	Node*				tmp;

	tmp = this->_lastNode;
	while (tmp != NULL)
	{
		tmp->dump(); // A virer
		lst.push_front(tmp);
		tmp = tmp->parent;
	}
	std::cout << "Count = " << lst.size() - 1 << std::endl; // A virer
	return (lst);
}

std::list<Node*>	nextNodes(int size, Node* topNode, NodePool& pool, Manhattan& man) {
	static Node::Square const	offsets[4] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}}; //Naze
//	static Node::Square const	offsets[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; //Bon
	Node::Square		curr_pos0 = topNode->pos0;
	std::list<Node*>	tmp;
	Node*				node;
	
	for (int i = 0; i < 4; i++)
	{
		Node::Square checked;
		checked = curr_pos0 + offsets[i];
		if (checked.x >= 0 && checked.x < size && checked.y >= 0 && checked.y < size)
		{
			node = pool.newNode();
			*node = *topNode;
			*node->square(curr_pos0) = *node->square(checked);
			*node->square(checked) = 0;
			node->cost += 1;
			node->heuristic = man.distance(node->map);
			node->distance = node->cost + node->heuristic;
			node->pos0 = checked;
			node->parent = topNode;
			node->hash();
			tmp.push_back(node);
		}
	}
	return (tmp);
}

AStarSolver::AStarSolver(char **map, char **finalMap, int size)
	: _size(size), _pool(size), _openlist(&AStarSolver::less_node),
	  _closelist(100, &AStarSolver::hash_node, &AStarSolver::eq_node),
	  _firstNode(map, size),
	  _finalNode(finalMap, size), _man(finalMap, size)
{
	this->_firstNode.heuristic = this->_man.distance(map);
	this->_openlist.push(&this->_firstNode);
}

bool	AStarSolver::solve(void)
{
	Node* topNode = this->_openlist.top();
	this->_openlist.pop();
	this->_lastNode = topNode;
	if (topNode->heuristic == 0)
	{
		this->_closelist.insert(topNode);
		return (false);
	}
	for (Node* node : nextNodes(this->_size, topNode, this->_pool, this->_man))
	{
		if (this->_closelist.find(node) == this->_closelist.end())
		{
			this->_openlist.push(node);
		}
		else
		{
			this->_pool.delNode(node);
		}
	}
	this->_closelist.insert(topNode);
//	this->_lastNode = topNode;
	return true;
}

char	**AStarSolver::getSnailForm(char **map, int size) {
	char **newMap = new char*[size * size];
	int total_size = size * size;
	int x = 0;
	int y = 0;
	int ix = 1;
	int iy = 0;
	int	maxx = 2;
	int	maxy = 1;

	for (int i = 0; i < total_size; i++)
	{
		int nx = x + ix;
		int ny = y + iy;

		newMap[i] = &map[y][x];
		if (nx < 0 || nx >= size || (ix != 0 && (ix > 0 ? nx >= size + maxx - 1 : nx <= 0 - maxx)))
		{
			iy = ix;
			ix = 0;
			maxx -= 1;
		}
		else if (ny < 0 || ny >= size || (iy != 0 && (iy > 0 ? ny >= size + maxy - 1 : ny <= 0 - maxy)))
		{
			ix = -iy;
			iy = 0;
			maxy -= 1;
		}
		x += ix;
		y += iy;
	}
	return (newMap);
}

bool	AStarSolver::isSolvable(char **map, int size) {
	char	**newMap = getSnailForm(map, size);
	int		total_size = size * size;
	int		count = 0;

	for (int i = 0; i < total_size - 1; i++)
	{
		for (int j = i + 1; j < total_size; j++)
		{
			if (*newMap[i] && *newMap[j] && *newMap[i] > *newMap[j])
				count++;
		}
	}
	return (count % 2 == 0);
}

char	**AStarSolver::finalSolution(int size) {
	char	**newMap = new char*[size];
	int		total_size = size * size;
	char	**snailMap;

	for (int i = 0; i < size; i++)
	{
		newMap[i] = new char[size];
		memset(newMap[i], size, 0);
	}
	snailMap = getSnailForm(newMap, size);
	for (int i = 0; i < total_size - 1; i++)
	{
		*(snailMap[i]) = i + 1;
	}
	return (newMap);
}

char	**AStarSolver::genMap(size_t size, size_t swaps)
{
	char	**map = finalSolution(size);
	char	offsets[4][2] = {
		{1, 0}, {0, 1}, {-1, 0}, {0, -1}
	};
	int		count = 0;
	char	pos0[2] = {(char)(size / 2), (char)(size / 2 - (size % 2 == 0 ? 1 : 0))};

	if (swaps == 0)
	{
		swaps = rand() % 1400;
	}
	while (swaps > 0)
	{
		int		off = rand() % 4;
		char	swapPos[2] = {(char)(pos0[0] + offsets[off][0]), char(pos0[1] + offsets[off][1])};
		if (swapPos[0] >= 0 && swapPos[0] < (int)size && swapPos[1] >= 0 && swapPos[1] < (int)size)
		{
			map[(int)pos0[0]][(int)pos0[1]] = map[(int)swapPos[0]][(int)swapPos[1]];
			map[(int)swapPos[0]][(int)swapPos[1]] = 0;
			pos0[0] = swapPos[0];
			pos0[1] = swapPos[1];
		}
		count = (count + 1) & 0xF;
		swaps--;
	}
	return (map);
}
