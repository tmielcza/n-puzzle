#include "AStarSolver.hpp"

int main(int ac, char **av)
{

  if (ac  > 2)
    std::cout << "error" << std::endl;
  else
  {
    AStarSolver a;
    a.finalSolution(atoi(av[1]));
  }
  (void)av;
  return (0);
}
