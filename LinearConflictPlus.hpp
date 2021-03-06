#ifndef LINEARCONFLICTPLUS_HPP
# define LINEARCONFLICTPLUS_HPP

# include "Manhattan.hpp"
# include <vector>
# include <iostream>

class LinearConflictPlus : public Manhattan {

public:
  LinearConflictPlus();
  LinearConflictPlus(unsigned short **finalMap, size_t size);
  LinearConflictPlus(LinearConflictPlus const &src);
  ~LinearConflictPlus();

  LinearConflictPlus  &operator=(LinearConflictPlus const &rhs);
  virtual int		distance(const unsigned short * const *map) const;

private:
  std::vector<unsigned short> *rows;
  std::vector<unsigned short> *cols;
};

#endif // LINEARCONFLICTPLUS_HPP
