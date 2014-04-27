//
// Sfml.hh for nibbler in /home/nguyen_7//proj/cpp/nibbler
//
// Made by julien nguyen-duy
// Login   <nguyen_7@epitech.net>
//
// Started on  Mon Mar 14 12:11:14 2011 julien nguyen-duy
// Last update Sun Mar 20 23:13:31 2011 damien locque
//

#ifndef		__SFML_HH__
# define        __SFML_HH__

#include	<map>
#include	<SFML/System.hpp>
#include	<SFML/Window.hpp>
#include	<SFML/Graphics.hpp>
#include	"../srcs/IGui.hpp"
#include	"../srcs/myException.hh"

enum e_img
  {
    GROUND,
    ROCK,
    S_BODY,
    S_HEAD,
    POKEBALL
  };

enum libError {
  IMGLOAD,
  WIN,
  BADSIZE
};

class Sfml : public IGui
{
private :
  std::map<e_img, sf::Image>		_Img;
  std::map<e_block, sf::Sprite>		_Block;
  std::map<sf::Key::Code, e_mov>	_Key;
  sf::RenderWindow			_Window;
  sf::Event			        _Event;
  unsigned int				_Width;
  unsigned int				_Height;

public:
  explicit Sfml();
  virtual ~Sfml();
  virtual void				checkSize(int width, int length);
  virtual void				drawBlock(int posx, int posy, e_block type);
  virtual void				drawScore(unsigned int score);
  virtual void				refresh_win();
  virtual e_mov				getEvent();

private:
  void					initImg();
  void					setBlocks();
  void					setKeys();
  void					clearPrevscore(unsigned int score);

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

#endif		/* __SFML_HH__ */
