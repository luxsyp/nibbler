//
// Ndkpp.hh for  in /home/locque_d//rendu/proj/nibbler
//
// Made by damien locque
// Login   <locque_d@epitech.net>
//
// Started on  Tue Mar  8 14:12:40 2011 damien locque
// Last update Sat Mar 19 17:17:05 2011 julien nguyen-duy
//

#ifndef			__CORE_HH__
# define		__CORE_HH__

#include <map>
#include <list>
#include <vector>
#include "IGui.hpp"

typedef struct	s_chunk
{
  bool		is_head;
  e_mov		last_move;
  int		posx;
  int		posy;
}t_chunk;

enum e_action {
  EATSELF,
  TAKEWALL,
  MOVE
};

class Core
{
private:
  int					_timer;
  int					_width;
  int					_height;
  std::map<int,  std::vector<int> >	_map;
  std::list<t_chunk>			_snake;
  IGui					*_gui;
  unsigned int				_score;
  e_action				_action;

  void					create_snake();
  void					createMap();
  void					put_snake();
  void					do_move(t_chunk *, e_mov);
  void					put_new_block(e_block);

public:
  Core(IGui *, int, int);
  ~Core();
  e_mov					check_move(e_mov);
  e_action				move_snake(e_mov);
  unsigned int				getScore() const;
  void					setTimer(e_mov, int);
  int					getTimer() const;
  void					setAction(e_action);
  void					printEndgame() const;
};

#endif			/* __CORE_HH__ */
