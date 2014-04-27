//
// Nibbler.hh for nibbler in /home/nguyen_7//proj/cpp/nibbler
// 
// Made by julien nguyen-duy
// Login   <nguyen_7@epitech.net>
// 
// Started on  Thu Mar 17 10:57:57 2011 julien nguyen-duy
// Last update Sat Mar 19 17:09:30 2011 julien nguyen-duy
//

#ifndef			__NIBBLER_HH__
# define		__NIBBLER_HH__

#include "Core.hh"
#include "IGui.hpp"
#include "myException.hh"

enum nibblerError {
  BADARG,
  DLERROR
};

class Nibbler {
public:
  IGui		*_Gui;
  Core		*_Core;

public:
  Nibbler();
  ~Nibbler();

  bool		checkArg(char const *str) const;
  unsigned int	getnbr(char const *str) const;
  void		setGui(IGui *(*ext_ctor)());
  void		deleteGui();
  void	        setCore(unsigned int width, unsigned int height);
  Core		*getCore() const;
  void		execNibbler(unsigned int width, unsigned int height);
  void		doPause(e_mov *m, e_mov last) const;

  class nibblerException : public myException
  {
  private:
    nibblerError			_Type;

  public:
    explicit nibblerException(GamePart part, std::string const &error, nibblerError type);
    virtual ~nibblerException() throw();

    virtual char const		*what() const throw();
    virtual std::string		where() const;
  };
};

#endif			/* __NIBBLER_HH__ */
