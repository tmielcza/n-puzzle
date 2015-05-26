#include "AStarSolver.hpp"
#include "Parser.hpp"

int main(int ac, char **av)
{
	AStarSolver a;
	char **map2 = new char *[4];
	char map[4][4] = {
		{4, 3, 2, 5},
		{12, 1, 15, 14},
		{10, 11, 13, 6},
		{0, 9, 8, 7}
	};
	char **map3 = NULL;
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
		exit (-1);
	}
	if (ac == 1)
	{
		std::cout << "Map generation" << std::endl;
		for (size_t i = 0; i < sizeof(map[0]) / sizeof(map[0][0]); i++)
			map2[i] = &map[i][0];
		if (a.isSolvable(map2, sizeof(map[0])))
			a.solve(map2, sizeof(map[0]));
		else
		{
			std::cout << "Error : Not solvable." << std::endl;
			exit (-1);
		}
	}
	else
	{
		Parser b;
		map3 = b.get_map(av[1]);
		if (map3 != NULL)
		{
			std::cout << "here" << std::endl;
			if (a.isSolvable(map3, b.getSize()))
				a.solve(map3, b.getSize());
			else
			{
				std::cout << "Error : Not solvable." << std::endl;
				exit (-1);
			}
		}
		else
		{
			std::cout << "Error : Bad map." << std::endl;
			exit (-1);
		}
	}
	return (0);
}
