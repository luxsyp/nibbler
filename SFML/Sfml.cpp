//
// Sfml.cpp for nibbler in /home/nguyen_7//proj/cpp/nibbler
//
// Made by julien nguyen-duy
// Login   <nguyen_7@epitech.net>
//
// Started on  Mon Mar 14 14:38:46 2011 julien nguyen-duy
// Last update Sun Mar 20 23:24:57 2011 damien locque
//

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "../srcs/myException.hh"
#include "Sfml.hh"

Sfml::Sfml()
{
  this->initImg();
  this->setBlocks();
  this->setKeys();
}

Sfml::~Sfml()
{
}

void			Sfml::initImg()
{
 if (!(this->_Img[GROUND].LoadFromFile("../img/ground.png")))
    throw Sfml::libException(LIB, "../img/ground.png is not found", IMGLOAD);
  if (!(this->_Img[ROCK].LoadFromFile("../img/rock_ground.png")))
    throw Sfml::libException(LIB, "../img/rock_ground.png is not found", IMGLOAD);
  if (!(this->_Img[S_BODY].LoadFromFile("../img/topi_ground.png")))
    throw Sfml::libException(LIB, "../img/topi_ground.png is not found", IMGLOAD);
  if (!(this->_Img[S_HEAD].LoadFromFile("../img/trio_ground.png")))
    throw Sfml::libException(LIB, "../img/trio_ground.png is not found", IMGLOAD);
  if (!(this->_Img[POKEBALL].LoadFromFile("../img/pokeball_trans.png")))
    throw Sfml::libException(LIB, "../img/pokeball_trans.png is not found", IMGLOAD);
  this->_Img[POKEBALL].CreateMaskFromColor(sf::Color(255, 0, 0));
}

void			Sfml::setBlocks()
{
  this->_Block[VOID] = sf::Sprite(this->_Img[GROUND]);
  this->_Block[WALL] = sf::Sprite(this->_Img[ROCK]);
  this->_Block[BODY] = sf::Sprite(this->_Img[S_BODY]);
  this->_Block[HEAD] = sf::Sprite(this->_Img[S_HEAD]);
  this->_Block[APPLE] = sf::Sprite(this->_Img[POKEBALL]);
}

void			Sfml::setKeys()
{
  this->_Key[sf::Key::Escape] = QUIT;
  this->_Key[sf::Key::Up] = UP;
  this->_Key[sf::Key::Down] = DOWN;
  this->_Key[sf::Key::Left] = LEFT;
  this->_Key[sf::Key::Right] = RIGHT;
  this->_Key[sf::Key::P] = PAUSE;
  this->_Key[sf::Key::Add] = FAST;
  this->_Key[sf::Key::Subtract] = SLOW;
}

void			Sfml::drawBlock(int posx, int posy, e_block type)
{
  this->_Block[type].SetPosition(sf::Vector2f(posx * 22, posy * 22));
  this->_Window.Draw(this->_Block[type]);
}

void			Sfml::checkSize(int width, int height)
{
  if (width > (1280 / 22) || height > (1024 / 22))
    throw Sfml::libException(LIB, "The size is not possible", BADSIZE);
  this->_Window.Create(sf::VideoMode(22 * width, (22 * height) + 22, 32), "Nibbler SFML");
  if (!(this->_Window.IsOpened()))
    throw Sfml::libException(LIB, "Can't create a window", WIN);
  this->_Window.Clear();
  this->_Width = width;
  this->_Height = height;
}

void			Sfml::drawScore(unsigned int score)
{
  sf::String		scorestr;
  std::ostringstream	ss;

  if (score > 0)
    this->clearPrevscore(score - 1);
  ss << score;
  scorestr.SetText(" Score : " + ss.str());
  scorestr.SetSize(20);
  scorestr.SetColor(sf::Color(255, 255, 255));
  scorestr.SetPosition(sf::Vector2f(0, 22 * this->_Height));
  this->_Window.Draw(scorestr);
}

void			Sfml::clearPrevscore(unsigned int score)
{
  sf::String		scorestr;
  std::ostringstream	ss;

  ss << score;
  scorestr.SetText(" Score : " + ss.str());
  scorestr.SetSize(20);
  scorestr.SetColor(sf::Color(0, 0, 0));
  scorestr.SetPosition(sf::Vector2f(0, 22 * this->_Height));
  this->_Window.Draw(scorestr);
}

void			Sfml::refresh_win()
{
  this->_Window.Display();
}

e_mov			Sfml::getEvent()
{
  this->_Window.GetEvent(this->_Event);
  if (this->_Event.Type == sf::Event::Closed)
    {
      this->_Window.Close();
      return (QUIT);
    }
  if (this->_Event.Type == sf::Event::KeyPressed)
    if (this->_Key.find(this->_Event.Key.Code) != this->_Key.end())
      return (this->_Key[this->_Event.Key.Code]);
  return (UNKNOWN);
}

Sfml::libException::libException(GamePart part, std::string const &error, libError type)
  : myException(part, error), _Type(type)
{
}

Sfml::libException::~libException() throw()
{
}

const char		*Sfml::libException::what() const throw()
{
  return (this->_Error.c_str());
}

std::string		Sfml::libException::where() const
{
  switch (this->_Type)
    {
    case IMGLOAD :
      return ("[ERROR] Game Graphic Library : Image Load");
    case WIN :
      return ("[ERROR] Game Graphic Library : Window");
    case BADSIZE :
      return ("[ERROR] Game Graphic Library : Map Size");
    }
  return ("[ERROR] Game Graphic Library");
}

extern "C"
{
  IGui	*create()
  {
    return new Sfml();
  }
}
