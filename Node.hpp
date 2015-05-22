#ifndef NODE_HPP
# define NODE_HPP

template<size_t S>
struct Node
{
	char	map[S][S];
	int		cost;
	int		heuristic;
	Node<S>	*parent;
	char	pos0[2];
	Node(int cost, int heuristic, char pos0[2], Node *parent)
		: cost(cost), heuristic(heuristic), pos0(pos0), parent(parent) {}
};

#endif // NODE_HPP
