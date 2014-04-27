//
// Ncurse.hh for  in /home/locque_d//rendu/proj/nibbler
//
// Made by damien locque
// Login   <locque_d@epitech.net>
//
// Started on  Wed Mar  9 12:07:36 2011 damien locque
// Last update Sun Mar 20 23:08:55 2011 damien locque
//

#ifndef _NCURSE_HH_
#define _NCURSE_HH_

#include <map>
#include "../srcs/IGui.hpp"
#include "../srcs/myException.hh"

#define KEY_ESC		27
#define KEY_p		112
#define KEY_LESS	45
#define KEY_MORE	43

enum libError {
  INIT,
  BADSIZE,
  WIN,
  END
};

class Ncurse : public IGui
{
private :
  WINDOW			*_win;
  std::map <e_block, int>	_Nblock;
  std::map <int, e_mov>		_key;

public :
  explicit Ncurse();
  virtual ~Ncurse();
  virtual void		checkSize(int, int);
  virtual void		drawBlock(int , int, e_block);
  virtual void		drawScore(unsigned int);
  virtual void		refresh_win();
  virtual e_mov		getEvent();

private:
  void			initTerm();
  void			initColor();
  void			initBlocks();
  void			initKeys();

  void			xinit_pair(short pair, short f, short b) const;
  void			xmvwaddch(WINDOW *win, int y, int x, const chtype ch) const;

  class libException : public myException
  {
  private:
    libError			_Type;

  public:
    explicit libException(GamePart part, std::string const &error, libError type);
    virtual ~libException() throw();

    virtual char const		*what() const throw();
    virtual std::string		where() const;
  };
};

#endif /* !_NCURSE_HH_ */
