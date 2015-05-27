#include "AStarSolver.hpp"

int main(int ac, char **av)
{
	// char map[4][4] = {
	// 	{4, 3, 2, 5},
	// 	{12, 1, 15, 14},
	// 	{10, 11, 13, 6},
	// 	{0, 9, 8, 7}
	// };

	// cui la du forum
	char map[4][4] = {
	{4, 15, 1, 2},
	{0, 14, 8, 13},
	{10, 12, 3, 9},
	{11, 5, 7, 6}
	};

	// Hardcore mode ...
	// char map[4][4] = {
	// 	{0, 15, 14, 13},
	// 	{5, 4, 3, 12},
	// 	{6, 2, 1, 11},
	// 	{7, 8, 9, 10}
	// };

	/*
	  39 coups
	11 12 3 5
	10 9 13 1
	2 4 0 14
	8 7 15 6
	*/

	char **map2 = new char *[4];
	for (size_t i = 0; i < sizeof(map[0]) / sizeof(map[0][0]); i++)
	{
		map2[i] = &map[i][0];
	}
	if (ac  > 2)
		std::cout << "error" << std::endl;
	else
	{
		AStarSolver a;
//		a.finalSolution(atoi(av[1]));
		if (a.isSolvable(map2, sizeof(map[0])))
		{
			std::cout << "Solvable" << std::endl;
			a.solve(a.genMap(4, 300), 4);
//			a.solve(map2, sizeof(map[0]));
		}
		else
			std::cout << "Not Solvable" << std::endl;
	}
	(void)av;
	return (0);
}
