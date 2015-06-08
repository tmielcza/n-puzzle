#include "MisplacedTiles.hpp"

MisplacedTiles::~MisplacedTiles() {}

MisplacedTiles::MisplacedTiles(char **final_map, size_t size) : Manhattan(final_map, size) {}


int MisplacedTiles::distance(const char * const *map) const {
	int pos;
	int x_final;
	int y_final;
	int cumul = 0;

	for (int x = 0; x < this->size; x++)
	{
		for (int y = 0; y < this->size; y++)
		{
			if (map[y][x] == 0)
				continue ;
			pos = map[y][x];
			y_final = this->map_pos[pos].y;
			x_final = this->map_pos[pos].x;
			if (x != x_final)
        cumul++;
      if (y != y_final)
        cumul++;
		}
	}
	return (cumul);
}
