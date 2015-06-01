#include "Parser.hpp"

Parser::Parser() : size(0), justGetSize(false), numberLine(0) {}

Parser::~Parser() {}

// char *Parser::convert(char **map)
// {
//   int k = 0;
//   char *str = new char[this->size * this->size];
//   for (int i = 0; i < this->size; i++)
//   {
//     for (int j = 0; map[i][j] != '\0' ; j++)
//     {
//       std::cout <<  (int)map[i][j] << std::endl;
//       str[k] = map[i][j];
//       k++;
//     }
//   }
//   return (str);
// }

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
      while (line[j] != '\0' && line[j] != '#' && line[j] != '\n')
      {
        if (line[j] == ' ')
        {
          while (line[j] == ' ' && line[j] != '\0' && line[j] != '\n' && line[j] != '#')
            j++;
          if (line[j] != '\0' && line[j] != '\n' && line[j] != '#')
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
//  char *str;

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
        std::cout << "line = " <<  line << std::endl;
        int count = 0;
        int index = 0;
        for (int j = 0; line[j] != '\0' && line[j] != '#' && line[j] != '\n'; j++)
        {
    //      std::cout << "line[j] : " << line[j] << std::endl << "ascii : " << (int)line[j] << std::endl;
          while (isdigit(line[j]) != 0)
          {
            this->stockNumber += line[j];
            j++;
          }
          if (this->stockNumber != "")
          {
            std::cout << "stocknumber : " << this->stockNumber << std::endl;
            std::cout << count << std::endl;
            count++;
            if (count > this->size)
            {
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
  // str = convert(map_file);
  // std::sort(str, str+(size*size));
  // for (int i = 0; i < (size * size); i++)
  // {
  //   std::cout << "str : " << (int)str[i] << std::endl;
  //   if (str[i] != i)
  //     return NULL;
  // }



  // mettre dans un seul tableau. Trier. Checker que ca va bien jusqu a size*size - 1
  return map_file;
}

int Parser::getSize()
{
  return this->size;
}
