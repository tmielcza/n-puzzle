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

	void	setMap(const char * const * map) {
		for (size_t x = 0; x < this->size; x++)
		{
			for (size_t y = 0; y < this->size; y++)
			{
				this->map[y][x] = map[y][x];
			}
		}
	}

	Node(const char * const * map, int size, int cost, int heuristic, char pos0[2], Node *parent)
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

	Node(const Node& src) : size(src.size) {
		this->map = new char*[this->size];
		for (size_t i = 0; i < this->size; i++)
		{
			this->map[i] = new char[this->size];
		}
		*this = src;
	}

	Node&	operator=(const Node& rhs) {
		setMap(rhs.map);
		return (*this);
	}
};

bool	operator==(const Node& lhs, const Node& rhs) {
		if (lhs.size == rhs.size)
			return (true);
		else
			return (false);
	}

bool	operator<(const Node& lhs, const Node& rhs) {
		if (lhs.size < rhs.size)
			return (true);
		else
			return (false);
	}

#endif // NODE_HPP
