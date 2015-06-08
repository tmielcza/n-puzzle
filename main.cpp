#include <ctime>
#include <cstdlib>
#include "AStarSolver.hpp"
#include "Parser.hpp"
#include "HeuristicFactory.hpp"
#include "Dijkstra.hpp"

enum npuzzle_error_t {
	ERR_TOOMANYARGS,
	ERR_BADOPTS,
	ERR_BADHEURISTIC,
	ERR_NOTSOLVABLE,
	ERR_BADMAP
};

void error(npuzzle_error_t error, unsigned short **map)
{
	if (error == ERR_TOOMANYARGS)
		std::cout << "Too many args" << std::endl;
	else if (error == ERR_BADOPTS)
		std::cout << "Bad options" << std::endl;
	else if (error == ERR_BADHEURISTIC)
		std::cout << "Heuristic doesn't exist" << std::endl;
	else if (error == ERR_NOTSOLVABLE)
		std::cout << "Not solvable" << std::endl;
	else if (error == ERR_BADMAP)
		std::cout << "Bad map" << std::endl;
	if (map != NULL)
	{
		delete [] map[0];
		delete [] map;
	}
	std::exit(EXIT_FAILURE);
}

void	displayMap(unsigned short **map, size_t size) {
	for (size_t y = 0; y < size; y++)
	{
		for (size_t x = 0; x < size; x++)
		{
			if (map[y][x] == 0)
				std::cout << "\033[38;5;163m" << (int)map[y][x] << "\033\1330m ";
			else
				std::cout << (int)map[y][x] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void	retracePath(std::list<const Node*> &path, size_t size, std::string name, size_t beginid, size_t endid) {
	AStarSolver			*ass;
	HeuristicFactory&	heurfactory = HeuristicFactory::getInstance();
	auto				begin = path.begin();
	auto				end = path.end();

	for (size_t i = 0; i < beginid; i++) {
		begin++;
	}
	for (size_t i = 0; i < endid; i++) {
		end--;
	}
	ass = new AStarSolver((*begin)->map, (*end)->map, size,
						  *heurfactory.createHeuristic(name, (*end)->map, size));
	while (ass->solve()) ;
	auto	newList = ass->buildPath();
	begin = path.erase(begin, end)--;
	path.insert(begin, newList.begin(), --newList.end());
}

void	refinePath(std::list<const Node*> &path, size_t size, std::string name) {
	size_t		half_list = path.size() / 2;
	size_t		quarter_list = half_list / 2 / 2;
	if (quarter_list < 2) {
		return ;
	}
	retracePath(path, size, name, quarter_list, quarter_list);
	retracePath(path, size, name, 0, half_list);
	retracePath(path, size, name, half_list, 1);
}

void	runSolver(unsigned short **map, std::string heuristicName, int size, bool bidir) {
	AStarSolver				*a;
	IHeuristic				*ha;
	unsigned short					**finalMap;
	std::list<const Node*>	path;
	size_t					totalStates;
	size_t					maxStates;

	finalMap = AStarSolver::finalSolution(size);
	ha = HeuristicFactory::getInstance().createHeuristic(heuristicName, finalMap, size);
	if (ha == NULL)
		error(ERR_BADHEURISTIC, map);
	a = new AStarSolver(map, finalMap, size, *ha);
	if (!AStarSolver::isSolvable(map, size))
		error(ERR_NOTSOLVABLE, map);
	else if (!bidir) {
		while (a->solve()) ;
		path = a->buildPath();
		totalStates = a->getTotalStates();
		maxStates = a->getMaxStates();
	} else {
		AStarSolver			*b;
		IHeuristic			*hb;

		hb = HeuristicFactory::getInstance().createHeuristic(heuristicName, map, size);
		b = new AStarSolver(finalMap, map, size, *hb);
		while (a->solve() && b->solve() && !AStarSolver::collide(*a, *b) && !AStarSolver::collide(*b, *a)) ;
		path = AStarSolver::buildMultiPath(*a, *b);
		refinePath(path, size, "linearconflict");
		totalStates = a->getTotalStates() + b->getTotalStates();
		maxStates = a->getMaxStates() + b->getMaxStates();
	}
	for (auto atom : path)
		atom->dump();
	std::cout << "Count : " << path.size() - 1 << std::endl;
	std::cout << "Complexity in time : " << totalStates << std::endl;
	std::cout << "Complexity in size : " << maxStates << std::endl;
}

int main(int ac, char **av)
{
	int size = 0;
	unsigned short **map = NULL;
	std::string heuristic;
	Parser b;

	if (ac > 7)
		error(ERR_TOOMANYARGS, map);
	map = b.get_map(av[1]);
	if (map != NULL)
	{
		if (!b.get_options(ac, av))
			error(ERR_BADOPTS, map);
		if (b.getOptionSize() > 2 && b.getOptionSize() <= 17)
			size = b.getOptionSize();
		else
			error(ERR_BADOPTS, map);
		heuristic =  b.getOptionH();
		if (map[0][0] == 'O')
			map = AStarSolver::genMap(size, 0);
		else
			size = b.getSize();
		if (b.getOptionBi() == true)
			std::cout << "kikoo" << std::endl;
		displayMap(map, size);
		std::cout << "--------------------------------" << std::endl;
		runSolver(map, b.getOptionH(), size, b.getOptionBi());
	}
	else
		error(ERR_BADMAP, map);

	return (0);
}
