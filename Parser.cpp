#include "Parser.hpp"

Parser::Parser() : size(0), justGetSize(false), numberLine(0) {}

Parser::~Parser() {}

void Parser::remove(char **map)
{
  for (int i = 0; i < this->size; i++)
    delete map[i];
  delete map;
}

char *Parser::convert(char **map)
{
  int k = 0;
  char *str = new char[this->size * this->size];
  for (int i = 0; i < this->size; i++)
  {
    for (int j = 0; j < this->size ; j++)
    {
      str[k] = map[i][j];
      k++;
    }
  }
  return (str);
}

bool Parser::parsing(std::string line)
{
  int i = 0;
  std::string stock;
  int count = 0;

  this->comment = false;
  while (line[i] == ' ')
    i++;
  if (line[i] == '#')
  {
    this->comment = true;
    return true;
  }
  for (unsigned int j = i; line[j]; j++)
  {
    if (isdigit(line[j]) == 0 && line[j] != ' ')
    {
      if (line[j] == '#' && this->size != 0)
      {
        for (unsigned int k = 0; line[k] != '#'; k++)
        {
          while (isdigit(line[k]) != 0)
          {
            stock += line[k];
            k++;
          }
          if (stock != "")
          {
            count++;
            stock = "";
          }
        }
        if (count != this->size)
          return false;
        return true;
      }
      else
        return false;
    }
    if (isdigit(line[j]) != 0 && this->size == 0)
    {
      while (j < line.size() && line[j] != '#')
      {
        if (line[j] == ' ')
        {
          while (line[j] == ' ' && j < line.size() && line[j] != '#')
            j++;
          if (j < line.size() && line[j] != '#')
            return false;
        }
        this->stockSize += line[j];
        j++;
      }
      std::stringstream(this->stockSize) >> this->size;
      if (this->size <= 2)
        return false;
      this->justGetSize = true;
      return true;
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
  char *str;

  file.open(map);
  while (file.good())
  {
    getline(file, line);
    if (!parsing(line)) // ERROR
    {
      if (this->size != 0)
        remove(map_file);
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
        int count = 0;
        int index = 0;
        for (unsigned int j = 0; line[j] != '#' && j < line.size(); j++)
        {
          while (isdigit(line[j]) != 0)
          {
            this->stockNumber += line[j];
            j++;
          }
          if (this->stockNumber != "")
          {
            count++;
            if (count > this->size)
              return NULL;
            std::stringstream(this->stockNumber) >> number;
            map_file[this->numberLine][index] = number;
            this->stockNumber = "";
            index++;
          }
        }
        this->numberLine++;
      }
    }
  }
  if ((this->numberLine - 1) != this->size)
    return NULL;
 str = convert(map_file);
 std::sort(str, str+(size*size));
 for (int i = 0; i < (size * size); i++)
 {
   if (str[i] != i)
   {
     remove(map_file);
     delete str;
     return NULL;
   }
}
  delete str;
  return map_file;
}

int Parser::getSize()
{
  return this->size;
}
