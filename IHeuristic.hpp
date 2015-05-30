#ifndef IHEURISTIC_HPP
# define IHEURISTIC_HPP

class IHeuristic {
public:
	virtual size_t	distance(char **map) = 0;
};

#endif // IHEURISTIC_HPP
