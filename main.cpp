#include <ctime>
#include "AStarSolver.hpp"
#include "Parser.hpp"
#include "Manhattan.hpp"
#include "LinearConflict.hpp"


int main(int ac, char **av)
{
	int size = 0;
	char **map = NULL;

	if (ac > 2) {
		std::cout << "Error." << std::endl;
		exit (1);
	}
	if (ac == 1)
	{
		std::cout << "Map generation" << std::endl;
		size = arc4random() % 14 + 3;
		map = AStarSolver::genMap(size, 0);
	}
	else
	{
		Parser b;
		map = b.get_map(av[1]);
		size = b.getSize();
	}
	if (map != NULL)
	{
		LinearConflict	heur(AStarSolver::finalSolution(size), size);
		AStarSolver a(map, AStarSolver::finalSolution(size), size, heur);
		if (AStarSolver::isSolvable(map, size))
		{
			while (a.solve());
			for (auto atom : a.buildPath())
			{
				atom->dump();
			}
			std::cout << "Count : " << a.buildPath().size() << std::endl;
		}
		else
		{
			std::cout << "Error : Not solvable." << std::endl;
			exit (1);
		}
	}
	else
	{
		std::cout << "Error : Bad map." << std::endl;
		exit (1);
	}
	return (0);
}
