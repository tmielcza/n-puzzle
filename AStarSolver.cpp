#include "AStarSolver.hpp"

AStarSolver::AStarSolver() {}

AStarSolver::~AStarSolver() {}

bool	AStarSolver::solve(char **map, size_t size) {
	(void)map;
	(void)size;
	return true;
}

#include <cstdio>


char	**getSnailForm(char **map, int size) {
	char **newMap = new char*[size * size];
	int total_size = size * size;
	int x = 0;
	int y = 0;
	int ix = 1;
	int iy = 0;
	int	maxx = 2;
	int	maxy = 1;

	for (int i = 0; i < total_size; i++)
	{
		int nx = x + ix;
		int ny = y + iy;

		newMap[i] = &map[y][x];
		if (nx < 0 || nx >= size || (ix != 0 && (ix > 0 ? nx >= size + maxx - 1 : nx <= 0 - maxx)))
		{
			iy = ix;
			ix = 0;
			maxx -= 1;
		}
		else if (ny < 0 || ny >= size || (iy != 0 && (iy > 0 ? ny >= size + maxy - 1 : ny <= 0 - maxy)))
		{
			ix = -iy;
			iy = 0;
			maxy -= 1;
		}
		x += ix;
		y += iy;
	}
	return (newMap);
}

bool	AStarSolver::isSolvable(char **map, int size) {
	char **newMap = getSnailForm(map, size);
	int total_size = size * size;
	int count = 0;

	for (int i = 0; i < total_size - 1; i++)
	{
		for (int j = i + 1; j < total_size; j++)
		{
			if (*newMap[i] && *newMap[j] && *newMap[i] > *newMap[j])
				count++;
		}
	}
	return (count % 2 == 0);
}


char **AStarSolver::finalSolution(int size) {
	char **newMap = new char*[size];
	int total_size = size * size;
	char **snailMap;

	for (int i = 0; i < size; i++)
	{
		newMap[i] = new char[size];
		memset(newMap[i], size, 0);
	}
	snailMap = getSnailForm(newMap, size);
	for (int i = 0; i < total_size - 1; i++)
	{
		*(snailMap[i]) = i + 1;
	}
	return (newMap);
}

