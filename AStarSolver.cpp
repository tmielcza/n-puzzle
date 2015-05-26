#include <queue>
#include <unordered_set>
#include <list>
#include "AStarSolver.hpp"
#include "Node.hpp"

AStarSolver::AStarSolver() {}

AStarSolver::~AStarSolver() {}

int	hash_node(const Node* node)
{
	int	hash = 0;
	int	i = 0;

	for (size_t x = 0; x < node->size; x++)
	{
		for (size_t y = 0; y < node->size; y++, i++)
		{
			hash ^= node->map[y][x] & (0xF << ((i << 2) & 31));
		}
	}
	return (hash);
}

bool	eq_node(const Node* a, const Node* b)
{
	return (*a == *b);
}

bool	less_node(const Node* a, const Node* b)
{
	return (a->heuristic > b->heuristic);
}

void				dumpNode(Node* node)
{
	for (size_t y = 0; y < node->size; y++)
	{
		for (size_t x = 0; x < node->size; x++)
		{
			std::cout << (int)node->map[y][x] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::list<Node*>	buildPath(Node* last)
{
	std::list<Node*>	lst;

	while (last != NULL)
	{
		dumpNode(last);
		lst.push_front(last);
		last = last->parent;
	}
	std::cout << "Count = " << lst.size() << std::endl;
	return (lst);
}

#include <unistd.h>

typedef std::unordered_set<Node*, decltype(&hash_node), decltype(&eq_node)>	nodes_set;
typedef std::priority_queue<Node*, std::vector<Node*>, decltype(&less_node)> node_queue;

bool	AStarSolver::solve(char **map, const int size)
{
	node_queue openlist(less_node);
	nodes_set closelist(100, hash_node, eq_node);
	char **final_map;
	final_map = finalSolution(size);
	char testouille[2] = {1, 2};
	Node	final_node(final_map, size, 0, 0, testouille, NULL);
	char pos0[2];

	for (int i = 0; i < size * size; i++)
	{
		if (map[i / size][i % size] == 0)
		{
			pos0[0] = i / size;
			pos0[1] = i % size;
			break;
		}
	}
	openlist.push(new Node(map, size, 0, manhattanDistance(map, final_map, size), pos0, NULL));
	while (1)
	{
		const char offsets[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
		if (*openlist.top() == final_node)
		{
			buildPath(openlist.top());
			return true;
		}
		unsigned short curr_pos0[2];
		curr_pos0[0] = openlist.top()->pos0[0];
		curr_pos0[1] = openlist.top()->pos0[1];
		Node* topNode = openlist.top();
		openlist.pop();
		std::cout << topNode->heuristic << " - " << openlist.size() << std::endl;
		for (int i = 0; i < 4; i++)
		{
			unsigned short checked[2];
			checked[0] = curr_pos0[0] + offsets[i][0];
			checked[1] = curr_pos0[1] + offsets[i][1];
			if (checked[0] >= 0 && checked[0] < size && checked[1] >= 0 && checked[1] < size)
			{
				Node* node = new Node(*topNode);
				node->map[curr_pos0[0]][curr_pos0[1]] = node->map[checked[0]][checked[1]];
				node->map[checked[0]][checked[1]] = 0;
				if (closelist.find(node) == closelist.end())
				{
					node->cost += 1;
					node->heuristic = node->cost + manhattanDistance(node->map, final_map, size);
					node->pos0[0] = checked[0];
					node->pos0[1] = checked[1];
					node->parent = topNode;
					openlist.push(node);
				}
				else
				{
					delete node;
				}
			}
		}
		closelist.insert(topNode);
	}

	return true;
}

int	AStarSolver::manhattanDistance(char **map, char **map_final, int size) {
	char map_pos[16][2];
	int pos;
	int x_final;
	int y_final;
	int cumul = 0;

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			pos = map_final[y][x];
			map_pos[pos][0] = y;
			map_pos[pos][1] = x;
		}
	}
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			pos = map[y][x];
			y_final = map_pos[pos][0];
			x_final = map_pos[pos][1];
			cumul += abs(x_final - x);
			cumul += abs(y_final - y);
		}
	}
	return (cumul);
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
	char **newMap = getSnailForm(map, size);
	int total_size = size * size;
	int count = 0;

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

char **AStarSolver::finalSolution(int size) {
	char **newMap = new char*[size];
	int total_size = size * size;
	char **snailMap;

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
