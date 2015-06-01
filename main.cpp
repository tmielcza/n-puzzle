#include <ctime>
#include "AStarSolver.hpp"
#include "Parser.hpp"
#include "Manhattan.hpp"

int main(int ac, char **av)
{
	int size = 0;
	char **map = NULL;

	// char **map2 = new char *[4];
	// char map[4][4] = {
	// 	{4, 3, 2, 5},
	// 	{12, 1, 15, 14},
	// 	{10, 11, 13, 6},
	// 	{0, 9, 8, 7}
	// };

	// cui la du forum
	// char map[4][4] = {
	// {4, 15, 1, 2},
	// {0, 14, 8, 13},
	// {10, 12, 3, 9},
	// {11, 5, 7, 6}
	// };

	// Hardcore mode = 80 coups...
	// char map[4][4] = {
	// 	{15, 14, 13, 12},
	// 	{10, 11, 8, 9},
	// 	{2, 6, 5, 1},
	// 	{3, 7, 4, 0}
	// };

	if (ac > 2) {
		std::cout << "Error." << std::endl;
		exit (1);
	}
	if (ac == 1)
	{
		std::cout << "Map generation" << std::endl;
		size = rand() % 14 + 3;
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
		Manhattan	heur(AStarSolver::finalSolution(size), size);
		AStarSolver a(map, AStarSolver::finalSolution(size), size, heur);
		if (AStarSolver::isSolvable(map, size))
		{
			while (a.solve());
			for (auto atom : a.buildPath())
			{
				atom->dump();
			}
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
