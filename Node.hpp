#ifndef NODE_HPP
# define NODE_HPP

# include <cstddef>

struct Node
{
	struct	Square {
		Square(int x, int y) : x(x), y(y) {}
		Square(void) {}
		int	x;
		int	y;
	};

			Node(size_t size);
			Node();
			Node(const Node& src);
			Node(const char * const * map, int size);
			Node(const char * const * map, int size, int cost, int heuristic, char pos0[2], Node *parent);
	void	setMap(const char * const * map);
	Square	find0(const char * const * map, size_t size);
	void	dump(void) const;
	char*	square(const Square& s) const;
	void	hash(void);

	Node&	operator=(const Node& rhs);

	char	**map;
	size_t	size;
	int		cost;
	int		heuristic;
	int		distance;
	Node	*parent;
	Square	pos0;
	size_t	_hash;
};

Node::Square	operator+(Node::Square lhs, const Node::Square& rhs);

bool	operator==(const Node& lhs, const Node& rhs);
bool	operator<(const Node& lhs, const Node& rhs);

#endif // NODE_HPP
