//
// Ndkpp.cpp for  in /home/locque_d//rendu/proj/nibbler
//
// Made by damien locque
// Login   <locque_d@epitech.net>
//
// Started on  Tue Mar  8 14:19:13 2011 damien locque
// Last update Mon Mar 21 14:05:39 2011 damien locque
//

#include <map>
#include <list>
#include <vector>
#include <cstdlib>
#include <limits.h>
#include <iostream>
#include "Core.hh"
#include "myException.hh"

Core::Core(IGui *gui, int width, int height) :
  _timer(250), _width(width), _height(height), _gui(gui), _score(0), _action(MOVE)
{
  std::vector<int>		tmp(this->_width);

  if (width < 8 || height < 8)
    throw myException(CORE, "Bad size value");
  gui->checkSize(width, height);
  srand(time(0));
  for (int y = 0 ; y < this->_height ; ++y)
    {
      for (int x = 0 ; x < this->_width ; ++x)
	tmp[x] = (int)VOID;
      this->_map.insert(std::pair<int, std::vector<int> >(y, tmp));
    }
  this->create_snake();
  this->put_snake();

  if (width >= 30 && height >= 30)
    this->createMap();

  for (int y = 0 ; y < this->_height ; ++y)
    for (int x = 0 ; x < this->_width ; ++x)
      this->_gui->drawBlock(x, y, (e_block)(this->_map[y])[x]);

  this->put_new_block(APPLE);
  this->_gui->drawScore(this->_score);
  this->_gui->refresh_win();
}

Core::~Core()
{

}

void			Core::setTimer(e_mov mov, int timer)
{
  if (mov == FAST && (this->_timer - timer > 50))
    this->_timer -= timer;
  else if (mov == SLOW && (this->_timer + timer < 1000))
    this->_timer += timer;
}

int			Core::getTimer() const
{
  return (this->_timer);
}

void			Core::create_snake()
{
  t_chunk		tmp;

  for (int s = 0 ; s < 4 ; s++)
    {
      tmp.is_head = (s > 0) ? false : true;
      tmp.last_move = LEFT;
      tmp.posx = (this->_width / 2) + s;
      tmp.posy = (this->_height / 2);
      this->_snake.push_back(tmp);
    }
}

void			Core::createMap()
{
  for (int y = 4 ; y < (this->_height - 4) ; ++y)
    if (y != (this->_height / 2) && y != (this->_height / 2) - 1
        &&  y != (this->_height / 2) + 1)
      {
        (this->_map[y])[4] = WALL;
        (this->_map[y])[this->_width - 5] = WALL;
      }
  for (int i = 0 ; i < 2 ; i++)
    {
      (this->_map[10])[this->_width / 2 + i] = WALL;
      (this->_map[this->_height - 11])[this->_width / 2 + i] = WALL;
      (this->_map[10])[this->_width / 2 - i] = WALL;
      (this->_map[this->_height - 11])[this->_width / 2 - i] = WALL;
    }
}

void			Core::put_snake()
{
  for (std::list<t_chunk>::iterator it = this->_snake.begin() ; it != this->_snake.end() ; ++it)
    (this->_map[(*it).posy])[(*it).posx] = (*it).is_head ? 2 : 1;
}

void			Core::put_new_block(e_block b)
{
  int			x;
  int			y;

  for (int i = 0 ; i < INT_MAX ; ++i)
    {
      x = rand() % this->_width;
      y = rand() % this->_height;
      if ((this->_map[y])[x] == 0)
	{
	  (this->_map[y])[x] = (int)b;
	  this->_gui->drawBlock(x, y, b);
	  return;
	}
    }
}

void			Core::do_move(t_chunk *tmp, e_mov mov)
{
  switch (mov)
    {
    case UP:
      tmp->posy = (this->_snake.front().posy == 0) ? this->_height - 1 : this->_snake.front().posy - 1;
      tmp->posx = this->_snake.front().posx;
      break;

    case DOWN:
      tmp->posy = (this->_snake.front().posy == this->_height -1) ? 0 : this->_snake.front().posy + 1;
      tmp->posx = this->_snake.front().posx;
      break;

    case LEFT:
      tmp->posx = (this->_snake.front().posx == 0) ? this->_width -1 : this->_snake.front().posx - 1;
      tmp->posy = this->_snake.front().posy;
      break;

    case RIGHT:
      tmp->posx = (this->_snake.front().posx == this->_width -1) ? 0 : this->_snake.front().posx + 1;
      tmp->posy = this->_snake.front().posy;
      break;

    default :
      break;
    }
}

e_action		Core::move_snake(e_mov mov)
{
  t_chunk		tmp;
  bool			grow;

  grow = false;
  if (mov == UNKNOWN)
    return (MOVE);
  tmp.last_move = mov;
  tmp.is_head = true;

  this->_snake.front().is_head = false;
  (this->_map[(this->_snake.front()).posy])[(this->_snake.front()).posx] = (int)BODY;
  this->_gui->drawBlock((this->_snake.front()).posx, (this->_snake.front()).posy, BODY);

  this->do_move(&tmp, mov);
  if ((this->_map[tmp.posy])[tmp.posx] == (int)APPLE)
    {
      this->_score += 1;
      this->put_new_block(APPLE);
      this->_gui->drawScore(this->_score);
      grow = true;
    }

  if (!grow)
    {
      (this->_map[(this->_snake.back()).posy])[(this->_snake.back()).posx] = (int)VOID;
      this->_gui->drawBlock((this->_snake.back()).posx, (this->_snake.back()).posy, VOID);
      this->_snake.pop_back();
    }

  if ((this->_map[tmp.posy])[tmp.posx] == (int)BODY)
    return (EATSELF);

  if ((this->_map[tmp.posy])[tmp.posx] == (int)WALL)
    return (TAKEWALL);

  (this->_map[tmp.posy])[tmp.posx] = 2;
  this->_gui->drawBlock(tmp.posx, tmp.posy, HEAD);
  this->_gui->refresh_win();
  this->_snake.push_front(tmp);
  return (MOVE);
}

e_mov			Core::check_move(e_mov mov)
{
  switch (mov)
    {
    case UP:
      if (this->_snake.front().last_move == DOWN)
	return (UNKNOWN);
      break;

    case DOWN:
      if (this->_snake.front().last_move == UP)
	return (UNKNOWN);
      break;

    case LEFT:
      if (this->_snake.front().last_move == RIGHT)
	return (UNKNOWN);
      break;

    case RIGHT:
      if (this->_snake.front().last_move == LEFT)
	return (UNKNOWN);
      break;

    default :
      return (mov);
      break;
    }
  return (mov);
}

unsigned int		Core::getScore() const
{
  return (this->_score);
}

void			Core::setAction(e_action action)
{
  this->_action = action;
}

void			Core::printEndgame() const
{
  if (this->_action == EATSELF)
    std::cout << "You ate yourself" << std::endl;
  else if (this->_action == TAKEWALL)
    std::cout << "You took a wall" << std::endl;
  std::cout << "Score : " << this->_score << std::endl;
}
