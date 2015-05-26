#include "Parser.hpp"

Parser::Parser() : size(0), justGetSize(false), numberLine(0) {}

Parser::~Parser() {}

bool Parser::parsing(std::string line)
{
  int i = 0;

  this->comment = false;
  while (line[i] == ' ')
    i++;
  if (line[i] == '#')
  {
    this->comment = true;
    return true;
  }
  for (int j = i; line[j]; j++)
  {

    if (isdigit(line[j]) == 0 && line[j] != ' ')
      return false;
    if (isdigit(line[j]) != 0 && this->size == 0)
    {
      while (line[j] != '\0' && line[j] != '#')
      {
        if (line[j] == ' ')
        {
          std::cout << line[j];
          while (line[j] == ' ' && line[j] != '\0')
            j++;
          if (line[j] != '\0')
            return false;
        }
        this->stockSize += line[j];
        j++;
      }
      std::stringstream(this->stockSize) >> this->size;
      if (this->size <= 2)
        return false;
      this->justGetSize = true;
    }
  }
  return true;
}

char **Parser::get_map(char *map)
{
  std::ifstream file;
  std::string line;
  char **map_file;
  int number = 0;

  file.open(map);
  while (file.good())
  {
    getline(file, line);
    if (!parsing(line)) // ERROR
    {
      if (this->size != 0)
      {
        // boucle pour del map_file
        delete(map_file);
      }
      return NULL;
    }
    else if (this->justGetSize) // creation map
    {
      map_file = new char*[this->size];
      for (int i = 0; i < this->size; i++)
        map_file[i] = new char[this->size];
      this->justGetSize = false;
    }
    else // enregistrement map
    {
      if (this->comment == false)
      {
        int index = 0;
        for (int j = 0; line[j] != '\0' && line[j] != '#' && line[j] != '\n'; j++)
        {
          while (isdigit(line[j]) != 0)
          {
            this->stockNumber += line[j];
            j++;
          }
          if (this->stockNumber != "")
          {
            std::stringstream(this->stockNumber) >> number;
            map_file[this->numberLine][index] = number;
            this->stockNumber = "";
            index++;
          }
        }
        if (this->numberLine >= this->size)
          break;
        this->numberLine++;
      }
    }
  }
  for (int i = 0; i < this->size; i++)
  {
    for (int j = 0; j < this->size; j++)
    {
      std::cout << (int)map_file[i][j] << " ";
    }
    std::cout << std::endl;
  }
  // mettre dans un seul tableau. Trier. Checker que ca va bien jusqu a size*size - 1
  return map_file;
}

int Parser::getSize()
{
  return this->size;
}
