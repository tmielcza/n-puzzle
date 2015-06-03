#include <ctime>
#include <cstdlib>
#include "AStarSolver.hpp"
#include "Parser.hpp"
#include "Manhattan.hpp"
#include "LinearConflict.hpp"

typedef enum {
	ERR_TOOMANYARGS,
	ERR_BADOPTS,
	ERR_BADHEURISTIC,
	ERR_NOTSOLVABLE,
	ERR_BADMAP
} npuzzle_error_t;

void error(npuwzzle_error_t error, char **map)
{
	if (error == ERR_TOOMANYARGS)
		std::cout << "Too many args" << std::endl;
	else if (error == ERR_BADOPTS)
		std::cout << "Bad options" << std::endl;
	else if (error == ERR_BADHEURISTIC)
		std::cout << "Heuristic doesn't exist" << std::endl;
	else if (error == ERR_NOTSOLVABLE)
		std::cout << "Not solvable" << std::endl;
	else if (error == ERR_BADMAP)
		std::cout << "Bad map" << std::endl;
	if (map != NULL)
	{
		std::cout << "clean map" << std::endl;
	}
	std::exit(EXIT_FAILURE);
}

int main(int ac, char **av)
{
	int size = rand() % 14 + 3;
	char **map = NULL;
	bool bi = false;
	std::string heuristic;
	std::string manhattan("manhattan");
	std::string linearconflict("linearconflict");
	Parser b;

	if (ac > 7)
		error(ERR_TOOMANYARGS, map);
	map = b.get_map(av[1]);
	size = b.getSize();
	if (map != NULL)
	{
		if (!b.get_options(ac, av))
			error(ERR_BADOPTS, map);
		if (b.getOptionSize() > 2 && b.getOptionSize() < 17)
			size = b.getOptionSize();
		heuristic =  b.getOptionH();
		bi = b.getOptionBi();
		if (map[0][0] == 'O')
			map = AStarSolver::genMap(size, 0);
		Manhattan	heur(AStarSolver::finalSolution(size), size);
		if (heuristic == linearconflict)
			LinearConflict	heur(AStarSolver::finalSolution(size), size);
		else if (heuristic != manhattan)
			error(ERR_BADHEURISTIC, map);
		AStarSolver a(map, AStarSolver::finalSolution(size), size, heur);
		if (AStarSolver::isSolvable(map, size))
		{
			while (a.solve());
			for (auto atom : a.buildPath())
				atom->dump();
			std::cout << "Count : " << a.buildPath().size() << std::endl;
		}
		else
			error(ERR_NOTSOLVABLE, map);
	}
	else
		error(ERR_BADMAP, map);

	return (0);
}
