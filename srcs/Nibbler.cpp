//
// Nibbler.cpp for nibbler in /home/nguyen_7//proj/cpp/nibbler
//
// Made by julien nguyen-duy
// Login   <nguyen_7@epitech.net>
//
// Started on  Thu Mar 17 11:13:30 2011 julien nguyen-duy
// Last update Sat Mar 19 20:02:32 2011 richard kim
//

#include <iostream>
#include <sstream>
#include "Nibbler.hh"
#include "Core.hh"
#include "myException.hh"

Nibbler::Nibbler()
  : _Gui(NULL), _Core(NULL)
{
}

Nibbler::~Nibbler()
{
  if (this->_Core != NULL)
    delete this->_Core;
}

unsigned int		Nibbler::getnbr(char const *str) const
{
  std::istringstream	iss(str);
  unsigned int		nb;

  iss >> nb;
  return (nb);
}

bool			Nibbler::checkArg(char const *str) const
{
  int			i = 0;

  while (str[i])
    {
      if (str[i] < '0' || str[i] > '9')
	return (false);
      i++;
    }
  return (true);
}

void			Nibbler::setCore(unsigned int width, unsigned int height)
{
  this->_Core = new Core(this->_Gui, width, height);
}

Core			*Nibbler::getCore() const
{
  return (this->_Core);
}

void			Nibbler::setGui(IGui *(*ext_ctor)())
{
  this->_Gui = ext_ctor();
}

void			Nibbler::deleteGui()
{
  if (this->_Gui != NULL)
    {
      delete this->_Gui;
      this->_Gui = NULL;
    }
}

void			Nibbler::doPause(e_mov *m, e_mov last) const
{
  bool			pause = false;

  while (!pause)
    {
      if (this->_Gui->getEvent() == PAUSE)
	{
	  pause = true;
	  *m = last;
	}
      usleep(200);
    }

}

void			Nibbler::execNibbler(unsigned int width, unsigned int height)
{
  e_mov			m = LEFT;
  e_mov			last;
  bool			end = false;
  e_action		action;

  this->setCore(width, height);
  while (!end)
    {
      for (int i = 0 ; i < 151 && !end ; ++i)
	{
	  if (m != PAUSE)
	    last = m;
	  m = this->_Gui->getEvent();
	  if (m == SLOW || m == FAST)
	    {
	      this->_Core->setTimer(m, 25);
	      m = last;
	    }
	  else if (m == PAUSE)
	    this->doPause(&m, last);
	  else if (m == QUIT)
	    end = true;
	  m = this->_Core->check_move(m);
	  if (m == UNKNOWN)
	    m = last;
	  usleep(this->_Core->getTimer());
	}
      if (!end && ((action = this->_Core->move_snake(m)) == EATSELF || action == TAKEWALL))
	{
	  this->_Core->setAction(action);
	  break;
	}
    }
}

Nibbler::nibblerException::nibblerException(GamePart part, std::string const &error, nibblerError type)
  : myException(part, error), _Type(type)
{
}

Nibbler::nibblerException::~nibblerException() throw()
{
}

const char		*Nibbler::nibblerException::what() const throw()
{
  return (this->_Error.c_str());
}

std::string		Nibbler::nibblerException::where() const
{
  switch (this->_Type)
    {
    case BADARG :
      return ("[ERROR] Game Launch : Bad Argument");
    case DLERROR :
      return ("[ERROR] Game Launch : DL Error");
    }
  return ("[ERROR] Game Launch");
}
