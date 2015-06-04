#include <ctime>
#include <cstdlib>
#include "AStarSolver.hpp"
#include "Parser.hpp"
#include "Manhattan.hpp"
#include "LinearConflict.hpp"
#include "MisplacedTiles.hpp"

typedef enum {
	ERR_TOOMANYARGS,
	ERR_BADOPTS,
	ERR_BADHEURISTIC,
	ERR_NOTSOLVABLE,
	ERR_BADMAP
} npuzzle_error_t;

void error(npuzzle_error_t error, char **map)
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
	int size = arc4random() % 14 + 3;
	char **map = NULL;
	std::string heuristic;
	Parser b;

	if (ac > 7)
		error(ERR_TOOMANYARGS, map);
	map = b.get_map(av[1]);
	if (map != NULL)
	{
		if (!b.get_options(ac, av))
			error(ERR_BADOPTS, map);
		if (b.getOptionSize() > 2 && b.getOptionSize() < 17)
			size = b.getOptionSize();
		heuristic =  b.getOptionH();
		if (map[0][0] == 'O')
			map = AStarSolver::genMap(size, 0);
		else
			size = b.getSize();
		if (b.getOptionBi() == true)
			std::cout << "kikoo" << std::endl;
		Manhattan	heur(AStarSolver::finalSolution(size), size);
		if (heuristic != "" && heuristic == "linearconflict")
			LinearConflict	heur(AStarSolver::finalSolution(size), size);
		else if (heuristic != "" && heuristic == "misplacedtiles")
			MisplacedTiles heur(AStarSolver::finalSolution(size), size);
		else if (heuristic != "" && heuristic != manhattan)
			error(ERR_BADHEURISTIC, map);
		AStarSolver a(map, AStarSolver::finalSolution(size), size, heur);
		if (AStarSolver::isSolvable(map, size))
		{
			std::cout << "I m aliiiive" << std::endl;
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
