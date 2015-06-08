#include "Parser.hpp"

Parser::Parser() : size(0), justGetSize(false), numberLine(0), optionH(""), optionBi(false), optionSize(arc4random() % 14 + 3) {}

Parser::~Parser() {}

bool Parser::get_options(int ac, char **av)
{
  int s = 0;
  int b = 0;
  int h = 0;
  int f = 0;
  std::string size;
  std::ifstream file;
  std::string name_h;

  if (ac == 1)
    return true;
  for (int i = 1; i != ac; i++)
  {
    if (strcmp(av[i], "-b") == 0)
      b += 1;
    else if (strcmp(av[i], "-h") == 0)
    {
      if (av[i + 1] == NULL)
        return false;
      i++;
      name_h = av[i];
      h += 1;
    }
    else if (strcmp(av[i], "-s") == 0)
    {
      if (av[i + 1] == NULL)
        return false;
      i++;
      int k = 0;
      while (av[i][k] != '\0')
      {
        if (av[i][k] <= 48 && av[i][k] >= 57)
          return false;
        k++;
      }
      size = av[i];
      if (atoi(size.c_str()) > 17 && atoi(size.c_str()) < 3)
        return false;
      s += 1;
    }
    else
    {
      file.open(av[i]);
      if (file.fail())
         return false;
      else
        file.close();
      f += 1;
    }
  }
  if (s > 1 || b > 1 || h > 1 || f > 1)
    return false;
  if (f == 1 && s >= 1)
    return false;
  if (s == 1)
    std::stringstream(size) >> this->optionSize;
  if (b == 1)
    this->optionBi = true;
  if (h == 1)
    this->optionH += name_h;
  return true;
}

int Parser::getOptionSize()
{
  return this->optionSize;
}

std::string Parser::getOptionH()
{
  return this->optionH;
}

bool Parser::getOptionBi()
{
  return this->optionBi;
}

void Parser::remove(unsigned short **map)
{
	delete [] map[0];
	delete [] map;
}

char *Parser::convert(unsigned short **map)
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

unsigned short **Parser::get_map(char *map)
{
  std::ifstream file;
  std::string line;
  unsigned short **map_file;
  int number = 0;
  char *str;

  file.open(map);
  if (file.fail())
  {
    map_file = new unsigned short*[1];
    map_file[0] = new unsigned short[1];
    map_file[0][0] = 'O';
    return map_file;
  }
  while (file.good())
  {
    getline(file, line);
    if (!parsing(line)) // ERROR
    {
      if (this->size != 0 && this->numberLine != 0)
        remove(map_file);
      return NULL;
    }
    else if (this->justGetSize) // creation map
    {
      if (this->size < 3 || this->size > 17)
        return NULL;
      map_file = new unsigned short*[this->size];
	    map_file[0] = new unsigned short[this->size * this->size];
      for (int i = 1; i < this->size; i++)
        map_file[i] = map_file[0] + this->size * i;
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
            {
              if (this->size != 0)
                remove(map_file);
              return NULL;
            }
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
  if (((this->numberLine - 1) != this->size) || this->size == 0)
    return NULL;
  str = convert(map_file);
  std::sort(str, str+(size*size));
  for (int i = 0; i < (size * size); i++)
  {
   if ((int)str[i] != i)
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
