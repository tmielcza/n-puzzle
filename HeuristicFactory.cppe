#include "HeuristicFactory.hpp"
#include "Manhattan.hpp"
#include "LinearConflict.hpp"
#include "LinearConflictPlus.hpp"
#include "MisplacedTiles.hpp"
#include "Dijkstra.hpp"

HeuristicFactory::HeuristicFactory() {}

HeuristicFactory::~HeuristicFactory() {}

HeuristicFactory HeuristicFactory::_instance;

HeuristicFactory &HeuristicFactory::getInstance() {
	return HeuristicFactory::_instance;
}

IHeuristic *HeuristicFactory::createHeuristic(std::string name, char **finalMap, size_t size)
{
	IHeuristic *ret = NULL;

	if (name == "manhattan" || name == "")
		ret = new Manhattan(finalMap, size);
	else if (name == "linearconflict")
		ret = new LinearConflict(finalMap, size);
	else if (name == "misplacedtiles")
		ret = new MisplacedTiles(finalMap, size);
	else if (name == "zero")
		ret = new Dijkstra();
	else if (name == "linearconflictplus")
		ret = new LinearConflictPlus(finalMap, size);
	return ret;
}
