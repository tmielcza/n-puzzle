#ifndef MANHATTAN_HPP
# define MANHATTAN_HPP

# include "IHeuristic.hpp"
# include "Node.hpp"

class Manhattan : public IHeuristic {

public:
	Manhattan();
	Manhattan(Manhattan const &src);
	Manhattan(char **map_final, size_t size);
	~Manhattan();

	Manhattan &operator=(Manhattan const &rhs);
	virtual int	distance(const char * const *map) const;

protected:
	Node::Square	*map_pos;
	int				size;
};

#endif // MANHATTAN_HPP
