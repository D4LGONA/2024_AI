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
      return "�ش�";

  case ent_Mom:
      return "����";

  case ent_Dog:
      return "Ǫ��";

  default:
    return "UNKNOWN!";
  }
}

#endif