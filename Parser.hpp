#ifndef PARSER_HPP
# define PARSER_HPP


#include <fstream>
#include <iostream>
#include <sstream>

class Parser {
public:
  Parser();
  Parser(Parser const &src);
  ~Parser();

  Parser &operator=(Parser const &rhs);
  bool parsing(std::string line);
  char **get_map(char *map);
  int getSize(void);
  char *convert(char **map);

private:
  int size;
  bool justGetSize;
  std::string stockSize;
  std::string stockNumber;
  bool comment;
  int numberLine;

};

#endif
