#ifndef LINEARCONFLICT_HPP
# define LINEARCONFLICT_HPP

# include <list>
# include "Manhattan.hpp"
# include <iostream>

class LinearConflict : public Manhattan {

public:
  LinearConflict();
  LinearConflict(char **finalMap, size_t size);
  LinearConflict(LinearConflict const &src);
  ~LinearConflict();

  LinearConflict  &operator=(LinearConflict const &rhs);
  virtual int		distance(const char * const *map) const;

private:
  std::list<char> *rows;
  std::list<char> *cols;
};

#endif // LINEARCONFLICT_HPP
