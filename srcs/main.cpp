//
// main.cpp for  in /home/locque_d//rendu/proj/nibbler
//
// Made by damien locque
// Login   <locque_d@epitech.net>
//
// Started on  Tue Mar  8 11:52:26 2011 damien locque
// Last update Sat Mar 19 14:09:17 2011 julien nguyen-duy
//

#include <dlfcn.h>
#include <sstream>
#include <iostream>
#include "Nibbler.hh"
#include "Core.hh"
#include "IGui.hpp"
#include "myException.hh"

int			main(int ac, char **av)
{
  void			*handle;
  IGui			*(*ext_ctor)();
  Nibbler		nibbler;

  try
    {
      if (ac != 4)
	throw myException((GamePart)42, "Usage: ./nibbler width height libXXX.so");
      handle = dlopen(av[3], RTLD_LAZY);
      if (!handle)
	throw Nibbler::nibblerException(NIBBLER, dlerror(), DLERROR);
      ext_ctor = reinterpret_cast<IGui* (*)()>(dlsym(handle, "create"));
      if (!ext_ctor)
	throw Nibbler::nibblerException(NIBBLER, dlerror(), DLERROR);
      if (!nibbler.checkArg(av[1]) || !nibbler.checkArg(av[2]))
	throw Nibbler::nibblerException(NIBBLER, "Bad map values", BADARG);
      nibbler.setGui(ext_ctor);
      nibbler.execNibbler(nibbler.getnbr(av[1]), nibbler.getnbr(av[2]));
      nibbler.deleteGui();
      nibbler.getCore()->printEndgame();
      if (dlclose(handle) != 0)
	throw Nibbler::nibblerException(NIBBLER, dlerror(), DLERROR);
    }
  catch (myException const &ex)
    {
      nibbler.deleteGui();
      std::cerr << ex.where() << " : " << ex.what() << std::endl;
      return (1);
    }
  return (0);
}
