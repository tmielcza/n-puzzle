#include "AStarSolver.hpp"

AStarSolver::AStarSolver() {}

AStarSolver::~AStarSolver() {}

bool AStarSolver::solve(char **map, size_t size) {
  (void)map;
  (void)size;
  return true;
}

char **getSnailForm(char **map, int size) {
  char **newMap = new char*[size * size];
  int total_size = size * size;
  int x = 0;
  int y = 0;
  int ix = 1;
  int iy = 0;

  for (int i = 1; i < total_size; i++)
  {
    newMap[i] = &map[y][x];
    if (x + ix < 0 || x + ix >= size)
    {
      iy = ix;
      ix = 0;
    }
    else if (y + iy < 0 || y + iy >= size)
    {
      ix = -iy;
      iy = 0;
    }
    else if (newMap[y + iy][x + ix] != 0)
    {
      if (iy != 0)
      {
        ix = -iy;
        iy = 0;
      }
      else
      {
        iy = ix;
        ix = 0;
      }
    }
    x += ix;
    y += iy;
  }
  return (newMap);
}

char **AStarSolver::finalSolution(int size) {
  char **newMap = new char*[size];
  int total_size = size * size;
  int x = 0;
  int y = 0;
  int ix = 1;
  int iy = 0;

  for (int i = 0; i < size; i++)
    newMap[i] = new char[size];
  for (int i = 1; i < total_size; i++)
  {
    newMap[y][x] = i;
    if (x + ix < 0 || x + ix >= size)
    {
      iy = ix;
      ix = 0;
    }
    else if (y + iy < 0 || y + iy >= size)
    {
      ix = -iy;
      iy = 0;
    }
    else if (newMap[y + iy][x + ix] != 0)
    {
      if (iy != 0)
      {
        ix = -iy;
        iy = 0;
      }
      else
      {
        iy = ix;
        ix = 0;
      }
    }
    x += ix;
    y += iy;
  }
  return (newMap);
}
