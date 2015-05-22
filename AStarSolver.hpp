#ifndef ASTARSOLVER_HPP
# define ASTARSOLVER_HPP

# include <iostream>
# include <cstdlib>

class AStarSolver {

public:
	AStarSolver();
	AStarSolver(AStarSolver const &src);
	~AStarSolver();

	AStarSolver &operator=(AStarSolver const &rhs);
	bool solve(char **map, size_t size);
	char **finalSolution(int size);
	bool isSolvable(char **map, int size);
	
};

#endif
