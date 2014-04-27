//
// Opengl.hh for nibbler in /home/kim_r//Projets/cpp/nibbler
//
// Made by richard kim
// Login   <kim_r@epitech.net>
//
// Started on  Mon Mar 14 18:03:39 2011 richard kim
// Last update Sun Mar 20 23:22:38 2011 damien locque
//

#ifndef		_MYOPENGL_HH_
#define		_MYOPENGL_HH_

#include	<SDL/SDL_ttf.h>
#include	<SDL/SDL.h>
#include	<map>
#include	<list>
#include	"../srcs/IGui.hpp"
#include	"../srcs/myException.hh"

#define		DWIDTH 1024
#define		DHEIGHT 768
#define		CONV(X, SIZE) (-(SIZE) + ((X) * 2) + 1)

#define		IMG_BACKGROUND	"../img/background_opengl.bmp"
#define		IMG_FLOOR	"../img/floor_opengl.bmp"
#define		IMG_HEAD	"../img/head_opengl.bmp"
#define		IMG_BODY	"../img/body_opengl.bmp"
#define		IMG_WALL	"../img/wall_opengl.bmp"

typedef struct s_block
{
  int		posx;
  int		posy;
  e_block	block;
}		t_block;

typedef struct s_cam
{
  double eyeX;
  double eyeY;
  double eyeZ;
  double centerX;
  double centerY;
  double centerZ;
  double upX;
  double upY;
  double upZ;

  double angle_x;
  double angle_y;
  double angle_z;
}		t_cam;

enum libError {
  INIT,
  IMGLOAD,
  BADSIZE
};

class		myOpengl : public IGui
{
public :
  myOpengl();
  virtual ~myOpengl();
  virtual void		checkSize(int, int);
  virtual void		drawBlock(int, int, e_block);
  virtual void		drawScore(unsigned int);
  virtual void		refresh_win();
  virtual e_mov		getEvent();

private :
  bool			_sdl_init;
  int			_width;
  int			_height;
  SDL_Event		_event;
  bool			_fp;
  std::map<int, e_mov>	_key;
  std::list<t_block>	_wall;
  std::list<t_block>	_snake;
  t_block		_apple;
  GLuint		_wallList;
  GLuint		_background;
  GLuint		_cube;
  GLuint		_sphere;
  t_cam			_cam;
  GLuint		_t[6];
  unsigned int		_score;
  SDL_Surface		*_screen;

  bool			init_sdl();
  void			init_camera(t_cam *cam, int startx, int starty);
  void			set_cam();
  void			createCallList();
  void			loadTexture();
  void			createBackground();
  void			drawFloor(int width, int height);
  void			drawCube(int axe_x, int axe_y, e_block b);
  void			drawSphere(int axe_x, int axe_y);
  void			createCube();
  void			createSphere();
  GLuint		set_texture(SDL_Surface *TextureImage);

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

#endif /* ! _MY_OPENGL_HH_ */
