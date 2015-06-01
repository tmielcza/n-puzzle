#ifndef DIJKSTRA_HPP
# define DIJKSTRA_HPP

# include "IHeuristic.hpp"

class Dijkstra : public IHeuristic {
public:

	virtual int	distance(const char * const *map) const ;
};

#endif // DIJKSTRA_HPP
