#ifndef NODE_HPP
# define NODE_HPP

# include <cstddef>

struct Node
{
	char	**map;
	size_t	size;
	int		cost;
	int		heuristic;
	Node	*parent;
	char	pos0[2];

			Node(size_t size);
			Node();
			Node(const Node& src);
			Node(const char * const * map, int size, int cost, int heuristic, char pos0[2], Node *parent);
	void	setMap(const char * const * map);

	Node&	operator=(const Node& rhs);
};

bool	operator==(const Node& lhs, const Node& rhs);
bool	operator<(const Node& lhs, const Node& rhs);

#endif // NODE_HPP
