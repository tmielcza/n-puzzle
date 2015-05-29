#ifndef ASTARSOLVER_HPP
# define ASTARSOLVER_HPP

# include <iostream>
# include <cstdlib>
# include <cstdio>
# include <queue>
# include <unordered_set>
# include <list>
# include "Node.hpp"
# include "NodePool.hpp"
# include "Manhattan.hpp"

class AStarSolver {

public:
	AStarSolver();
	AStarSolver(char **map, char **finalMap, int size);
	AStarSolver(AStarSolver const &src);
	~AStarSolver();

	AStarSolver			&operator=(AStarSolver const &rhs);
	bool				solve(void);
	static char			**finalSolution(int size);
	static bool			isSolvable(char **map, int size);
	static char			**getSnailForm(char **map, int size);
	int					manhattanDistance(char **map, char **map2, int size);
	char				**genMap(size_t size, size_t swaps);
	std::list<Node*>	buildPath(void);

	static bool			eq_node(const Node* a, const Node* b);
	static size_t		hash_node(const Node* node);
	static bool			less_node(const Node* a, const Node* b);

	const Node*&		getLastNode(void);
	const void*&		getCloseList(void);

private:
	typedef std::unordered_set<Node*, decltype(&AStarSolver::hash_node), decltype(&AStarSolver::eq_node)>	nodes_set;
	typedef std::priority_queue<Node*, std::vector<Node*>, decltype(&AStarSolver::less_node)> node_queue;

	size_t		_size;
	NodePool	_pool;
	node_queue	_openlist;
	nodes_set	_closelist;
	Node		_firstNode;
	Node		_finalNode;
	Node*		_lastNode;
	Manhattan	_man;
};

#endif // ASTARSOLVER_HPP
