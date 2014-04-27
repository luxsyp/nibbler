//
// INibbler.hh for  in /home/locque_d//rendu/proj/nibbler
//
// Made by damien locque
// Login   <locque_d@epitech.net>
//
// Started on  Tue Mar  8 11:52:05 2011 damien locque
// Last update Sat Mar 19 15:01:41 2011 julien nguyen-duy
//

#ifndef			__IGUI_HPP__
# define		__IGUI_HPP__

enum e_block
  {
    VOID,
    BODY,
    HEAD,
    WALL,
    APPLE
  };

enum e_mov
  {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    PAUSE,
    QUIT,
    FAST,
    SLOW,
    UNKNOWN
  };


class IGui
{
public :
  virtual ~IGui() {}
  virtual void		checkSize(int, int) = 0;
  virtual void		drawBlock(int, int, e_block) = 0;
  virtual void		drawScore(unsigned int) = 0;
  virtual void		refresh_win() = 0;
  virtual e_mov		getEvent() = 0;
};

#endif			/* !__IGUI_HPP__ */
