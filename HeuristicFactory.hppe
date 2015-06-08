#ifndef HEURISTICFACTORY_HPP
# define HEURISTICFACTORY_HPP

# include <string>
# include "IHeuristic.hpp"

class HeuristicFactory {

public:
	static HeuristicFactory &getInstance();
	IHeuristic *createHeuristic(std::string name, char **finaleMap, size_t size);

private:
	HeuristicFactory();
	HeuristicFactory(HeuristicFactory const &src);
	~HeuristicFactory();

	HeuristicFactory &operator=(HeuristicFactory const &rhs);

	static HeuristicFactory _instance;
};

#endif // HEURISTICFACTORY_HPP
