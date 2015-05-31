#ifndef MANHATTAN_HPP
# define MANHATTAN_HPP

# include "IHeuristic.hpp"
# include "Node.hpp"

class Manhattan : public IHeuristic {
public:

				Manhattan(char **map_final, size_t size);
	virtual int	distance(const char * const *map) const;

private:
	Node::Square	*map_pos;
	int				size;
};

#endif // MANHATTAN_HPP
