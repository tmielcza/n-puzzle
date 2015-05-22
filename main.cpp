#include "AStarSolver.hpp"

int main(int ac, char **av)
{
	char map[4][4] = {
		{15, 12, 14, 5},
		{7, 10, 1, 0},
		{4, 6, 8, 13},
		{2, 11, 9, 3}
	};
	char **map2 = new char *[4];
	for (int i = 0; i < 4; i++)
	{
		map2[i] = &map[i][0];
	}
	if (ac  > 2)
		std::cout << "error" << std::endl;
	else
	{
		AStarSolver a;
//		a.finalSolution(atoi(av[1]));
		if (a.isSolvable(map2, 4))
			std::cout << "Solvable" << std::endl;
	}
	(void)av;
	return (0);
}
