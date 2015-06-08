#ifndef DIJKSTRA_HPP
# define DIJKSTRA_HPP

# include "IHeuristic.hpp"

class Dijkstra : public IHeuristic {
public:
	Dijkstra();
	Dijkstra(Dijkstra const &src);
	~Dijkstra();

	Dijkstra &operator=(Dijkstra const &rhs);
	virtual int	distance(const char * const *map) const ;
};

#endif // DIJKSTRA_HPP
