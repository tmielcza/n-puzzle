#include "Parser.hpp"

Parser::Parser() : size(0), justGetSize(false), numberLine(0), options("") {}

Parser::~Parser() {}


bool Parser::get_options(char **av)
{
  int s = 0;
  int b = 0;
  int h = 0;
  int f = 0;
  std::string size = "";
  std::ifstream file;
  std::string name_h = "";

  for (int i = 1; av[i] != '\0'; i++)
  {
    if (strcmp(av[i], "-b") == 0)
      b += 1;
    else if (strcmp(av[i], "-h") == 0)
    {
      if (av[i++])
        i++;
      else
        return false;
      if (strcmp(av[i], "manhattan") == 0 || strcmp(av[i], "linearconflict") == 0)
        name_h += av[i]; // verif que possible
      else
        return false;
      h += 1;
    }
    else if (strcmp(av[i], "-s") == 0)
    {
      if (av[i++])
        i++;
      else
        return false;
      int k = 0;
      while (av[i][k] != '\0')
      {
        if (av[i][k] <= 48 && av[i][k] >= 57)
          return false;
        k++;
      }
      size += av[i];
      if (atoi(size.c_str()) > 17)
        return false;
      s += 1;
    }
    else
    {
      file.open(av[i]);
      if (file.fail())
        return false;
      else
      {
        file.close();
        f += 1;
      }
    }
  }
  if (s > 1 || b > 1 || h > 1 || f > 1)
    return false;
  if (f == 1 && s >= 1)
    return false;
  if (s == 1)
    this->options += "size = " + size + " ";
  if (b == 1)
    this->options += " b ";
  if (h == 1)
    this->options += "heuristic = " + name_h;

  return true;
}

std::string Parser::getOptions()
{
  return this->options;
}

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
  if (file.fail())
  {
    map_file = new char*[1];
    map_file[0] = new char[1];
    map_file[0][0] = 'O';
    return map_file;
  }
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
