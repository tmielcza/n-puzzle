#include <cstdlib>
#include "Manhattan.hpp"

Manhattan::Manhattan(char **map_final, size_t size) {
	this->map_pos = new Node::Square[size * size];
	this->size = (int)size;
	int pos;
	for (int x = 0; x < this->size; x++)
	{
		for (int y = 0; y < this->size; y++)
		{
			pos = map_final[y][x];
			map_pos[pos] = Node::Square(x, y);
		}
	}
}

int		Manhattan::distance(char **map) {
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
//			if (x_final != x && y_final != y)
//				cumul += 2;
			cumul += std::abs(x_final - x);
			cumul += std::abs(y_final - y);
		}
	}
	return (cumul);
}
