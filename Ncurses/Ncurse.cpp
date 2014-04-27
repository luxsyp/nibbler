//
// Ncurse.cpp for  in /home/locque_d//rendu/proj/nibbler
//
// Made by damien locque
// Login   <locque_d@epitech.net>
//
// Started on  Wed Mar  9 12:07:11 2011 damien locque
// Last update Sun Mar 20 23:09:08 2011 damien locque
//

#include <map>
#include <sstream>
#include <iostream>
#include <term.h>
#include <ncurses.h>
#include <signal.h>
#include "../srcs/IGui.hpp"
#include "../srcs/myException.hh"
#include "Ncurse.hh"

Ncurse::Ncurse()
  : _win(NULL)
{
  initscr();
  this->initTerm();
  this->initColor();
  timeout(0); // disable wait
  this->initBlocks();
  this->initKeys();
}

Ncurse::~Ncurse()
{
  if (this->_win != NULL)
    {
      if (delwin(this->_win) == ERR)
	throw Ncurse::libException(LIB, "Can't delete the window", END);
    }
  if (endwin() == ERR)
    throw Ncurse::libException(LIB, "Can't restore the terminal", END);
}

void			Ncurse::initTerm()
{
  if (keypad(stdscr, true) == ERR)
    throw Ncurse::libException(LIB, "Keypad activation failed", INIT);
  if (noecho() == ERR)
    throw Ncurse::libException(LIB, "NoEcho mode activation failed", INIT);
  if (curs_set(0) == ERR)
    throw Ncurse::libException(LIB, "Can't disable cursor", INIT);
  if (start_color() == ERR)
    throw Ncurse::libException(LIB, "Color activation failed", INIT);
  if (!has_colors())
    throw Ncurse::libException(LIB, "Your terminal does not support color", INIT);
}

void			Ncurse::initColor()
{
  xinit_pair(1, COLOR_BLACK, COLOR_BLACK);
  xinit_pair(2, COLOR_GREEN, COLOR_BLACK);
  xinit_pair(3, COLOR_YELLOW, COLOR_BLACK);
  xinit_pair(4, COLOR_BLACK, COLOR_MAGENTA);
  xinit_pair(5, COLOR_RED, COLOR_BLACK);
}

void			Ncurse::initBlocks()
{
  this->_Nblock.insert(std::pair<e_block, int>(VOID, 1));
  this->_Nblock.insert(std::pair<e_block, int>(HEAD, 2));
  this->_Nblock.insert(std::pair<e_block, int>(BODY, 3));
  this->_Nblock.insert(std::pair<e_block, int>(WALL, 4));
  this->_Nblock.insert(std::pair<e_block, int>(APPLE, 5));
}

void			Ncurse::initKeys()
{
  this->_key.insert(std::pair<int, e_mov>(KEY_UP, UP));
  this->_key.insert(std::pair<int, e_mov>(KEY_DOWN, DOWN));
  this->_key.insert(std::pair<int, e_mov>(KEY_LEFT, LEFT));
  this->_key.insert(std::pair<int, e_mov>(KEY_RIGHT, RIGHT));
  this->_key.insert(std::pair<int, e_mov>(KEY_MORE, FAST));
  this->_key.insert(std::pair<int, e_mov>(KEY_LESS, SLOW));
  this->_key.insert(std::pair<int, e_mov>(KEY_p, PAUSE));
  this->_key.insert(std::pair<int, e_mov>(KEY_ESC, QUIT));
}

void			Ncurse::checkSize(int width, int height)
{
  if ((width + 2) > tgetnum(const_cast<char *>("co")) ||
      (height + 2) > tgetnum(const_cast<char *>("li")))
    throw Ncurse::libException(LIB, "The size is not possible", BADSIZE);
  if (refresh() == ERR)
    throw Ncurse::libException(LIB, "Can't refresh the terminal", WIN);
  this->_win = newwin(height + 2, width + 2, 0, 0);
  if (this->_win == NULL)
    throw Ncurse::libException(LIB, "Can't create a new window", WIN);
  box(this->_win, 0, 0);
  this->refresh_win();
}

void			Ncurse::drawBlock(int posx, int posy, e_block b)
{
  if (wattron(this->_win, COLOR_PAIR(this->_Nblock[b])) == ERR)
    throw Ncurse::libException(LIB, "Can't activate block's color", WIN);
  if (b == APPLE)
    xmvwaddch(this->_win, posy + 1, posx + 1, 'o');
  else if (b == HEAD)
    xmvwaddch(this->_win, posy + 1, posx + 1, 'O');
  else if (b == BODY)
    xmvwaddch(this->_win, posy + 1, posx + 1, 'o');
  else
    xmvwaddch(this->_win, posy + 1, posx + 1, ' ');
  if (wattroff(this->_win, COLOR_PAIR(this->_Nblock[b])) == ERR)
    throw Ncurse::libException(LIB, "Can't desactivate block's color", WIN);
}

void			Ncurse::drawScore(unsigned int score)
{
  std::stringstream	ss;

  ss << score;
  if (mvaddstr(0, 1, " Score = ") == ERR
      || mvaddstr(0, 10, (ss.str() + " ").c_str()) == ERR)
    throw Ncurse::libException(LIB, "Can't print the score", WIN);
}

void			Ncurse::refresh_win()
{
  if (wrefresh(this->_win) == ERR)
    throw Ncurse::libException(LIB, "Can't refresh the window", WIN);
}

e_mov			Ncurse::getEvent()
{
  int	c;

  c = getch();
  if (this->_key.find(c) == this->_key.end())
    return (UNKNOWN);
  return (this->_key[c]);
}

void			Ncurse::xinit_pair(short pair, short f, short b) const
{
  if (init_pair(pair, f, b) == ERR)
    throw Ncurse::libException(LIB, "Can't initialize color", WIN);
}

void			Ncurse::xmvwaddch(WINDOW *win, int y, int x, const chtype ch) const
{
  if (mvwaddch(win, y, x, ch) == ERR)
    throw Ncurse::libException(LIB, "Can't move the block", WIN);
}


Ncurse::libException::libException(GamePart part, std::string const &error, libError type)
  : myException(part, error), _Type(type)
{
}

Ncurse::libException::~libException() throw()
{
}

const char		*Ncurse::libException::what() const throw()
{
  return (this->_Error.c_str());
}

std::string		Ncurse::libException::where() const
{
  switch (this->_Type)
    {
    case INIT :
      return ("[ERROR] Game Graphic Library : Initialization");
    case WIN :
      return ("[ERROR] Game Graphic Library : Window");
    case BADSIZE :
      return ("[ERROR] Game Graphic Library : Map Size");
    case END :
      return ("[ERROR] Game Graphic Library : Close");
    }
  return ("[ERROR] Game Graphic Library");
}

extern "C"
{
  IGui	*create()
  {
    return new Ncurse();
  }
}
