#include "AStarSolver.hpp"

int main(int ac, char **av)
{
// 	char map[4][4] = {
// 		{4, 3, 2, 5},
// 		{12, 1, 15, 14},
// 		{10, 11, 13, 6},
// 		{0, 9, 8, 7}
// 	};

//	cui la du forum
	char map[4][4] = {
	{4, 15, 1, 2},
	{0, 14, 8, 13},
	{10, 12, 3, 9},
	{11, 5, 7, 6}
	};

	// Hardcore mode ...
// 	char map[4][4] = {
// 		{0, 15, 14, 13},
// 		{5, 4, 3, 12},
// 		{6, 2, 1, 11},
// 		{7, 8, 9, 10}
// 	};

	char	**map2 = new char *[4];
	char	**finalMap = AStarSolver::finalSolution(4);
	for (size_t i = 0; i < sizeof(map[0]) / sizeof(map[0][0]); i++)
	{
		map2[i] = &map[i][0];
	}
	if (ac  > 2)
		std::cout << "error" << std::endl;
	else
	{
		Manhattan aheur(map2, 4);
		Manhattan bheur(finalMap, 4);
		AStarSolver a(map2, finalMap, 4, aheur);
		AStarSolver b(finalMap, map2, 4, bheur);
//		AStarSolver a(NULL, finalMap, 4);
//		a.finalSolution(atoi(av[1]));
//		if (a.isSolvable(map2, sizeof(map[0])))
		while (a.solve() && b.solve() && !AStarSolver::collide(a, b)
			   && !AStarSolver::collide(b, a))
//		while (b.solve())
		{
		}
		for (auto cul : AStarSolver::buildMultiPath(a, b))
		{
			cul->dump();
		}
//		b.buildPath();
	}
	(void)av;
	return (0);
}
