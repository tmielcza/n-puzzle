#include <ctime>
#include "AStarSolver.hpp"
#include "Parser.hpp"
#include "Manhattan.hpp"
#include "LinearConflict.hpp"



int main(int ac, char **av)
{
	int size = rand() % 14 + 3;
	std::string options = "";
	char **map = NULL;
	bool bi = false;
	std::string stocksize;
	std::size_t pos;

	if (ac > 6)
	{
		std::cout << "Error" << std::endl;
		exit (1);
	}
	Parser b;
	map = b.get_map(av[1]);
	size = b.getSize();
	if (map != NULL)
	{
		if (!b.get_options(av))
		{
			std::cout << "Error" << std::endl;
			exit (1);
		}
		options = b.getOptions();
		if (strncmp(options.c_str(), " b ", 3) == 0)
			bi = true;
		if (options.find("heuristic = ") != std::string::npos)
		{
			char heuristic[20];
			pos = options.find("heuristic = ") + 12;
			int k = 0;
			for (unsigned int i = pos; i < options.size() && options[i] != ' '; i++)
			{
				heuristic[k] = options[i];
				k++;
			}
			heuristic[k] = '\0';
		}
		if (options.find("size = ") != std::string::npos)
		{
			pos = options.find("size = ") + 7;
			for (unsigned int i = pos; i < options.size() && options[i] != ' '; i++)
				stocksize += options[i];
			std::stringstream(stocksize) >> size;
		}
		if (map[0][0] == 'O')
			map = AStarSolver::genMap(size, 0);
		LinearConflict	heur(AStarSolver::finalSolution(size), size);
		AStarSolver a(map, AStarSolver::finalSolution(size), size, heur);
		if (AStarSolver::isSolvable(map, size))
		{
			while (a.solve());
			for (auto atom : a.buildPath())
				atom->dump();
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
