#ifndef NAMES_H
#define NAMES_H

#include <string>

enum 
{
  ent_daughter,
  ent_Mom,
  ent_Dog
};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_daughter:
      return "ÇØ´Ô";

  case ent_Mom:
      return "¾ö¸¶";

  case ent_Dog:
      return "Çªµù";

  default:
    return "UNKNOWN!";
  }
}

#endif