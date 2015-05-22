#ifndef ASTARSOLVER_HPP
# define ASTARSOLVER_HPP

# include <iostream>
# include <cstdlib>
# include <cstdio>


class AStarSolver {

public:
	AStarSolver();
	AStarSolver(AStarSolver const &src);
	~AStarSolver();

	AStarSolver &operator=(AStarSolver const &rhs);
	bool solve(char **map, size_t size);
	char **finalSolution(int size);
	bool isSolvable(char **map, int size);
	char	**getSnailForm(char **map, int size);
	int	manhattanDistance(char **map, char **map2, int size);

};

#endif // ASTARSOLVER_HPP
