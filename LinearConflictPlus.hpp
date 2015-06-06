#ifndef LINEARCONFLICTPLUS_HPP
# define LINEARCONFLICTPLUS_HPP

# include "Manhattan.hpp"
# include <vector>
# include <iostream>

class LinearConflictPlus : public Manhattan {

public:
  LinearConflictPlus();
  LinearConflictPlus(char **finalMap, size_t size);
  LinearConflictPlus(LinearConflictPlus const &src);
  ~LinearConflictPlus();

  LinearConflictPlus  &operator=(LinearConflictPlus const &rhs);
  virtual int		distance(const char * const *map) const;

private:
  std::vector<char> *rows;
  std::vector<char> *cols;
};

#endif // LINEARCONFLICTPLUS_HPP
