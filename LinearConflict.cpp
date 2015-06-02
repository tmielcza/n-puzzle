# include "LinearConflict.hpp"
# include <unistd.h>

LinearConflict::LinearConflict(char **final_map, size_t size) : Manhattan(final_map, size) {
  this->rows = new std::list<char>[this->size];
  this->cols = new std::list<char>[this->size];
}

LinearConflict::~LinearConflict() {}

int		LinearConflict::distance(const char * const *map) const {

  int cumul = Manhattan::distance(map);

  for (int y = 0; y < this->size; y++)
  {
    for (int x = 0; x < this->size; x++)
    {
      int num = (int)map[y][x];
      Node::Square s = this->map_pos[num];
      if (num != 0)
      {
        if (s.x == x ) // virer le cast
          this->cols[x].push_back(s.y);
        if (s.y == y) // Pareil
          this->rows[y].push_back(s.x);
      }
    }
  }
  for (int k = 0; k < this->size; k++)
  {
    for (auto i = this->rows[k].begin(); i != this->rows[k].end(); i++)
    {
      for (auto j = (++i)--; j != this->rows[k].end(); j++)
      {
        if (*i > *j)
        {
          cumul += 2;
        }
      }
    }
  }
  for (int k = 0; k < this->size; k++)
  {
    for (auto i = this->cols[k].begin(); i != this->cols[k].end(); i++)
    {
      for (auto j = (++i)--; j != this->cols[k].end(); j++)
      {
        if (*i > *j)
          cumul += 2;
      }
    }
  }
  for (int i = 0; i < this->size; i++)
  {
    this->cols[i].clear();
    this->rows[i].clear();
  }
  return cumul;
}
