//
// myException.cpp for nibbler in /home/nguyen_7//proj/cpp/nibbler
// 
// Made by julien nguyen-duy
// Login   <nguyen_7@epitech.net>
// 
// Started on  Wed Mar 16 14:36:14 2011 julien nguyen-duy
// Last update Sat Mar 19 17:09:58 2011 julien nguyen-duy
//

#include <string>
#include "myException.hh"

myException::myException(GamePart part, std::string const &error)
  : _Part(part), _Error(error)
{
}

myException::~myException() throw()
{
}

char const		*myException::what() const throw()
{
  return (this->_Error.c_str());
}

std::string		myException::where() const
{
  switch (this->_Part)
    {
    case NIBBLER:
      return ("[ERROR] Game Launch");
    case CORE :
      return ("[ERROR] Game Core");
    case LIB :
      return ("[ERROR] Game Graphic Library");
    }
  return ("[ERROR]");
}
