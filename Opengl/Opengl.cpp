//
// Opengl.cpp for nibbler in /home/kim_r//Projets/cpp/nibbler
//
// Made by richard kim
// Login   <kim_r@epitech.net>
//
// Started on  Mon Mar 14 18:03:28 2011 richard kim
// Last update Wed May  4 14:20:46 2011 damien locque
//

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <sstream>
#include <iostream>
#include "Opengl.hh"

void		myOpengl::init_camera(t_cam *cam, int startx, int starty)
{
  cam->eyeX = startx + 10;
  cam->eyeY = 0;
  cam->eyeZ = starty + 8;
  cam->centerX = 0;
  cam->centerY = 0;
  cam->centerZ = 0;
  cam->upX = 0;
  cam->upY = 0;
  cam->upZ = 1;

  cam->angle_x = 0;
  cam->angle_y = 0;
  cam->angle_z = -2;
}

bool		myOpengl::init_sdl()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    throw myOpengl::libException(LIB, "SDL init failed", INIT);
  this->_sdl_init = true;
  if (!(this->_screen = SDL_SetVideoMode(DWIDTH, DHEIGHT, 32, SDL_OPENGL)))
    throw myOpengl::libException(LIB, "Set VideoMode failed", INIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(75, ((double)DWIDTH / DHEIGHT), 1, 1000);
  if (SDL_EnableKeyRepeat(10, 10) == -1)
    std::cerr << "SDL EnableKeyRepeat failed" << std::endl;
  glClearColor(0, 0, 0, 0.5);
  glEnable(GL_DEPTH_TEST);
  glClearDepth(1);

  this->loadTexture();
  this->createBackground();
  this->createCube();
  this->createSphere();
  return (true);
}

myOpengl::myOpengl() : _sdl_init(false), _fp(false),
		       _wallList(0), _background(0), _cube(0), _sphere(0)
{
  this->_key[SDLK_ESCAPE] = QUIT;
  this->_key[SDLK_RIGHT] = RIGHT;
  this->_key[SDLK_LEFT] = LEFT;
  this->_key[SDLK_DOWN] = DOWN;
  this->_key[SDLK_UP] = UP;
  this->_key[SDLK_p] = PAUSE;
  this->_key[SDLK_KP_PLUS] = FAST;
  this->_key[SDLK_KP_MINUS] = SLOW;
  this->_apple.posx = -1;
  this->_apple.posy = -1;
}

myOpengl::~myOpengl()
{
  glDisable(GL_TEXTURE_2D);
  if (this->_wallList != 0)
    glDeleteLists(this->_wallList, 1);
  if (this->_background != 0)
    glDeleteLists(this->_background, 2);
  if (this->_cube != 0)
    glDeleteLists(this->_cube, 3);
  if (this->_sphere != 0)
    glDeleteLists(this->_sphere, 4);
  if (this->_sdl_init)
    SDL_Quit();
}

GLuint		myOpengl::set_texture(SDL_Surface *TextureImage)
{
  GLuint	texture;

  if (!TextureImage)
    {
      std::cerr << "SDL Texture load failed" << std::endl;
      return (-1);
    }
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->w,
	       TextureImage->h, 0, GL_BGR,
	       GL_UNSIGNED_BYTE, TextureImage->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  if (TextureImage)
    SDL_FreeSurface(TextureImage);
  return (texture);
}

void		myOpengl::loadTexture()
{
  this->_t[0] = this->set_texture(SDL_LoadBMP(IMG_BACKGROUND));
  this->_t[1] = this->set_texture(SDL_LoadBMP(IMG_FLOOR));
  this->_t[2] = this->set_texture(SDL_LoadBMP(IMG_HEAD));
  this->_t[3] = this->set_texture(SDL_LoadBMP(IMG_BODY));
  this->_t[4] = this->set_texture(SDL_LoadBMP(IMG_WALL));
}

void		myOpengl::createBackground()
{
  this->_background = glGenLists(2);
  glNewList(this->_background, GL_COMPILE);

  gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
  glBindTexture(GL_TEXTURE_2D, this->_t[0]);
  glEnable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  glBegin(GL_QUADS);

  glTexCoord2f(1, 1);
  glVertex2f(-1, -1);
  glTexCoord2f(1, 0);
  glVertex2f(-1, 1);
  glTexCoord2f(0, 0);
  glVertex2f(1, 1);
  glTexCoord2f(0, 1);
  glVertex2f(1, -1);

  glEnd();
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_TEXTURE_2D);
  glEndList();
}

void		myOpengl::createSphere()
{
  GLUquadric*	params;

  params = gluNewQuadric();
  this->_sphere = glGenLists(4);
  glNewList(this->_sphere, GL_COMPILE);

  glColor3ub(35, 35, 35);
  gluSphere(params, 1, 20.0, 20.0);
  glColor3ub(227, 227, 227);
  gluCylinder(params, 1.1, 1.1, 0.2, 20, 20);
  glRotated(90, 1, 0, 0);
  gluCylinder(params, 1.1, 1.1, 0.2, 20, 20);
  gluDeleteQuadric(params);

  glEndList();
}

void		myOpengl::createCube()
{
  this->_cube = glGenLists(3);
  glNewList(this->_cube, GL_COMPILE);
  glEnable(GL_TEXTURE_2D);
  for (int i = 0; i < 4; i++)
    {
      glBegin(GL_QUADS);
      glTexCoord2d(0,1);
      glVertex3d(1,1,1);
      glTexCoord2d(0,0);
      glVertex3d(1,1,-1);
      glTexCoord2d(1,0);
      glVertex3d(-1,1,-1);
      glTexCoord2d(1,1);
      glVertex3d(-1,1,1);
      glEnd();
      glRotated(90,0,0,1);
    }
  glBegin(GL_QUADS);
  glTexCoord2d(0,0);
  glVertex3d(1,-1,1);
  glTexCoord2d(1,0);
  glVertex3d(1,1,1);
  glTexCoord2d(1,1);
  glVertex3d(-1,1,1);
  glTexCoord2d(0,1);
  glVertex3d(-1,-1,1);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glEndList();
}

void		myOpengl::drawSphere(int axe_x, int axe_y)
{
  glPushMatrix();
  glTranslated(axe_y, axe_x, 0.26);
  glCallList(this->_sphere);
  glPopMatrix();
  glColor3ub(255, 255, 255);
}

void		myOpengl::drawCube(int axe_x, int axe_y, e_block b)
{
  glPushMatrix();
    if (b == HEAD)
      glBindTexture(GL_TEXTURE_2D, this->_t[2]);
  else if (b == BODY)
    glBindTexture(GL_TEXTURE_2D, this->_t[3]);
  else if (b == WALL)
    glBindTexture(GL_TEXTURE_2D, this->_t[4]);
  glTranslated(axe_y, axe_x, 0);
  glCallList(this->_cube);
  glPopMatrix();
  glColor3ub(255, 255, 255);
}

void		myOpengl::drawFloor(int width, int height)
{
  glBindTexture(GL_TEXTURE_2D, this->_t[1]);
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  glBegin(GL_QUADS);

  glTexCoord2i(0, 0);
  glVertex3i(-height, -width, -1);

  glTexCoord2i(height, 0);
  glVertex3i(height, -width,-1);

  glTexCoord2i(height, width);
  glVertex3i(height, width, -1);

  glTexCoord2i(0, width);
  glVertex3i(-height, width, -1);

  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

void		myOpengl::checkSize(int width, int height)
{
  this->_width = width;
  this->_height = height;
  this->init_sdl();
  this->init_camera(&this->_cam, this->_width, this->_height);
}

void		myOpengl::createCallList()
{
  this->_wallList = glGenLists(1);
  glNewList(this->_wallList, GL_COMPILE);
  drawFloor(this->_width, this->_height);
  for (std::list<t_block>::iterator it = this->_wall.begin();
       it != this->_wall.end(); it++)
    drawCube(CONV((*it).posx, this->_width), CONV((*it).posy, this->_height), (*it).block);
  glEndList();
}

void		myOpengl::drawBlock(int posx, int posy, e_block b)
{
  static int	i = 0;
  t_block	tmp;

  tmp.posx = posx;
  tmp.posy = posy;
  tmp.block = b;
  if (b == APPLE)
    this->_apple = tmp;
  if (b == WALL && i < (this->_width * this->_height))
    this->_wall.push_back(tmp);
  if ((b == HEAD || b == BODY) && i < (this->_width * this->_height))
    this->_snake.push_back(tmp);
  else if (b == HEAD)
    {
      this->_snake.front().block = BODY;
      this->_snake.push_front(tmp);
    }
  if (b == VOID && i >= (this->_width * this->_height))
    this->_snake.pop_back();
  ++i;
  if (i == (this->_width * this->_height))
    createCallList();
}

void		myOpengl::set_cam()
{
  if (!this->_fp)
    {
      gluLookAt(this->_cam.eyeX, this->_cam.eyeY, this->_cam.eyeZ,
		this->_cam.centerX, this->_cam.centerY, this->_cam.centerZ,
		this->_cam.upX, this->_cam.upY, this->_cam.upZ);
      glRotated(this->_cam.angle_x, 1, 0, 0);
      glRotated(this->_cam.angle_y, 0, 1, 0);
      glRotated(this->_cam.angle_z, 0, 0, 1);
    }
  else
    gluLookAt(CONV(this->_snake.front().posy, this->_width) + 5,
	      CONV(this->_snake.front().posx, this->_height), 7,
	      CONV(this->_snake.front().posy, this->_width),
	      CONV(this->_snake.front().posx, this->_height) , 1,
	      0,0,1);
  glRotated(this->_cam.angle_x, 1, 0, 0);
  glRotated(this->_cam.angle_y, 0, 1, 0);
  glRotated(this->_cam.angle_z, 0, 0, 1);
}

void		myOpengl::refresh_win()
{
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glCallList(this->_background);
  this->set_cam();
  glCallList(this->_wallList);
  this->drawSphere(CONV(this->_apple.posx, this->_width),
	     CONV(this->_apple.posy, this->_height));
  for (std::list<t_block>::iterator it = this->_snake.begin();
       it != this->_snake.end(); it++)
    this->drawCube(CONV((*it).posx, this->_width),
	     CONV((*it).posy, this->_height), (*it).block);
  glFlush();
  SDL_GL_SwapBuffers();
}

e_mov		myOpengl::getEvent()
{
  static bool flag = true;
  SDL_PollEvent(&(this->_event));
  switch (this->_event.type)
    {
    case SDL_QUIT :
      return (QUIT);
    case SDL_KEYDOWN :
      if (this->_key.find(this->_event.key.keysym.sym) != this->_key.end())
	return (this->_key[this->_event.key.keysym.sym]);
      else
	switch (this->_event.key.keysym.sym)
	  {
	  case SDLK_a:
	    if (!this->_fp)
	      this->_cam.angle_z += 0.02;
	    break;
	  case SDLK_d:
	    if (!this->_fp)
	      this->_cam.angle_z -= 0.02;
	    break;
	  case SDLK_w:
	    if (!this->_fp)
	      this->_cam.eyeZ += 0.015;
	    break;
	  case SDLK_s:
	    if (!this->_fp)
	      this->_cam.eyeZ -= 0.015;
	    break;
	  case SDLK_ESCAPE:
	    return (QUIT);
	    break;
	  case SDLK_SPACE:
	    this->_fp =  this->_fp ? false : true;
	    break;
	  case SDLK_p :
	    if (flag == true)
	      {
		flag = false;
		return (PAUSE);
	      }
	    break;
	  default:
	    return (UNKNOWN);
	    break;
	  }
      break;
    }
  return (UNKNOWN);
}

void		myOpengl::drawScore(unsigned int score)
{
  this->_score = score;
}

myOpengl::libException::libException(GamePart part, std::string const &error, libError type)
  : myException(part, error), _Type(type) {}

myOpengl::libException::~libException() throw() {}

const char		*myOpengl::libException::what() const throw()
{
  return (this->_Error.c_str());
}

std::string		myOpengl::libException::where() const
{
  switch (this->_Type)
    {
    case INIT :
      return ("[ERROR] Game Graphic Library : Initialization");
    case IMGLOAD :
      return ("[ERROR] Game Graphic Library : Image Load");
    case BADSIZE :
      return ("[ERROR] Game Graphic Library : Map Size");
    }
  return ("[ERROR] Game Graphic Library");
}

extern "C"
{
  IGui *create()
  {
    return new myOpengl();
  }
}
