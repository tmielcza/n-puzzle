#ifndef MANHATTAN_HPP
# define MANHATTAN_HPP

# include "Node.hpp"

class Manhattan {
public:

			Manhattan(char **map_final, size_t size);
	int		distance(char **map);

private:
	Node::Square	*map_pos;
	int				size;
};

#endif // MANHATTAN_HPP
