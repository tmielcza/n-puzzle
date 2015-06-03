#include <ctime>
#include "AStarSolver.hpp"
#include "Parser.hpp"
#include "Manhattan.hpp"
#include "LinearConflict.hpp"

int main(int ac, char **av)
{
	int size = rand() % 14 + 3;
	char **map = NULL;
	bool bi = false;
	std::string heuristic;
	Parser b;

	if (ac > 7)
		goto error_args;
	map = b.get_map(av[1]);
	size = b.getSize();
	if (map != NULL)
	{
		if (!b.get_options(ac, av))
			goto error_options;
		if (b.getOptionSize() > 2 && b.getOptionSize() < 17)
			size = b.getOptionSize();
		heuristic =  b.getOptionH();
		bi = b.getOptionBi();
		if (map[0][0] == 'O')
			map = AStarSolver::genMap(size, 0);
		LinearConflict	heur(AStarSolver::finalSolution(size), size);
		AStarSolver a(map, AStarSolver::finalSolution(size), size, heur);
		if (AStarSolver::isSolvable(map, size))
		{
			while (a.solve());
			for (auto atom : a.buildPath())
				atom->dump();
			std::cout << "Count : " << a.buildPath().size() << std::endl;
		}
		else
			goto error_not_solvable;
	}
	else
		goto error_map;

	error_args:
		std::cout << "Too many args" << std::endl;
		exit (1);
	error_options:
		std::cout << "Bad options" << std::endl;
		exit (1);
	error_not_solvable:
		std::cout << "Not solvable" << std::endl;
		exit (1);
	error_map:
		std::cout << "Bad map" << std::endl;
		exit (1);

	return (0);
}
