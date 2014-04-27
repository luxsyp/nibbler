//
// myException.hh for nibbler in /home/nguyen_7//proj/cpp/nibbler
// 
// Made by julien nguyen-duy
// Login   <nguyen_7@epitech.net>
// 
// Started on  Wed Mar 16 11:03:41 2011 julien nguyen-duy
// Last update Sat Mar 19 17:10:07 2011 julien nguyen-duy
//

#ifndef			__MYEXCEPTION_HH__
# define		__MYEXCEPTION_HH__

#include <string>
#include <exception>
#include <stdexcept>

enum GamePart {
  NIBBLER,
  CORE,
  LIB
};

class myException : public std::exception
{
protected:
  GamePart	_Part;
  std::string	_Error;

public:
  explicit myException(GamePart part, std::string const &error);
  virtual ~myException() throw();

  virtual char const		*what() const throw();
  virtual std::string		where() const;
};

#endif			/* __MYEXCEPTION_HH__ */
