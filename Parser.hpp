#ifndef PARSER_HPP
# define PARSER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>

class Parser {

public:
  Parser();
  Parser(Parser const &src);
  ~Parser();

  Parser &operator=(Parser const &rhs);
  bool parsing(std::string line);
  unsigned short **get_map(char *map);
  int getSize(void);
  char *convert(unsigned short **map);
  bool get_options(int ac, char **av);
  std::string getOptionH(void);
  int getOptionSize();
  bool getOptionBi();

private:
  void remove(unsigned short **map);
  int size;
  bool justGetSize;
  std::string stockSize;
  std::string stockNumber;
  bool comment;
  int numberLine;
  std::string optionH;
  bool optionBi;
  int optionSize;
};

#endif
