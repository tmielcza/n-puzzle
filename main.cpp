#include <ctime>
#include <cstdlib>
#include "AStarSolver.hpp"
#include "Parser.hpp"
#include "HeuristicFactory.hpp"
#include "Dijkstra.hpp"

enum npuzzle_error_t {
	ERR_TOOMANYARGS,
	ERR_BADOPTS,
	ERR_BADHEURISTIC,
	ERR_NOTSOLVABLE,
	ERR_BADMAP
};

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
	int size = 0;
	char **map = NULL;
	std::string heuristic;
	Parser b;
	IHeuristic *heur;

	if (ac > 7)
		error(ERR_TOOMANYARGS, map);
	map = b.get_map(av[1]);
	if (map != NULL)
	{
		if (!b.get_options(ac, av))
			error(ERR_BADOPTS, map);
		if (b.getOptionSize() > 2 && b.getOptionSize() <= 17)
			size = b.getOptionSize();
		else
			error(ERR_BADOPTS, map);
		heuristic =  b.getOptionH();
		if (map[0][0] == 'O')
			map = AStarSolver::genMap(size, 0);
		else
			size = b.getSize();
		if (b.getOptionBi() == true)
			std::cout << "kikoo" << std::endl;

		heur = HeuristicFactory::getInstance().createHeuristic(b.getOptionH(), AStarSolver::finalSolution(size), size);
		if (heur == NULL)
			error(ERR_BADHEURISTIC, map);
		AStarSolver a(map, AStarSolver::finalSolution(size), size, *heur);
		if (AStarSolver::isSolvable(map, size))
		{
			std::cout << "I m aliiiive" << std::endl;
			while (a.solve()) ;
			for (auto atom : a.buildPath())
				atom->dump();
			std::cout << "Count : " << a.buildPath().size() - 1 << std::endl;
			std::cout << "Complexity in time : " << a.getTotalStates() << std::endl;
			std::cout << "Complexity in size : " << a.getMaxStates() << std::endl;
		}
		else
			error(ERR_NOTSOLVABLE, map);
	}
	else
		error(ERR_BADMAP, map);

	return (0);
}
