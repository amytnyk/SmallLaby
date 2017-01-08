#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <iostream>
#include <gl/GL.h>
#include <gl/GLU.h>

using namespace sf;

struct Coord3d
{
public:
  int X;
  int Y;
  int Z;
};

struct Wall
{
public:
  Coord3d A;
  Coord3d B;
  Coord3d C;
  Coord3d D;
};

Wall GenerateWall(int Ax, int Ay, int Az, int Bx, int By, int Bz, int Cx, int Cy, int Cz, int Dx, int Dy, int Dz)
{
  Wall wall;
  wall.A.X = Ax;
  wall.B.X = Bx;
  wall.C.X = Cx;
  wall.D.X = Dx;
  wall.A.Y = Ay;
  wall.B.Y = By;
  wall.C.Y = Cy;
  wall.D.Y = Dy;
  wall.A.Z = Az;
  wall.B.Z = Bz;
  wall.C.Z = Cz;
  wall.D.Z = Dz;
  return wall;
}

std::vector<Wall> GenerateWalls(std::vector<std::vector<int>> map, float size)
{
  std::vector<Wall> walls;
  for (size_t j = 0; j < map.size(); j++)
  {
    for (size_t i = 0; i < map[j].size(); i++)
    {
      float xl = i * size;
      float yt = j * size;
      float xr = (i + 1) * size;
      float yb = (j + 1) * size;
      if ((j != 0 && map[i][j] != map[i][j - 1]) || j == 0)//up
      {
        walls.push_back(GenerateWall(
          xl, yt, size, xl, yt, 0, xr, yt, 0, xr, yt, size
          ));
      }
      if ((j != map[i].size() - 1 && map[i][j] != map[i][j + 1]) || j == map[i].size() - 1)//down
      {
        walls.push_back(GenerateWall(
          xl, yb, size, xl, yb, 0, xr, yb, 0, xr, yb, size
          ));
      }
      if ((i != 0 && map[i][j] != map[i - 1][j]) || i == 0)//left
      {
        walls.push_back(GenerateWall(
          xl, yt, size, xl, yt, 0, xl, yb, 0, xl, yb, size
          ));
      }
      if ((i != map[i].size() - 1 && map[i][j] != map[i + 1][j]) || i == map[i].size() - 1)//right
      {
        walls.push_back(GenerateWall(
          xr, yt, size, xr, yt, 0, xr, yb, 0, xr, yb, size
          ));
      }
    }
  }
  return walls;
}

int main()
{
  RenderWindow window(sf::VideoMode(800, 600, 32), "SFML OpenGL");
  Clock Clock;
  glClearDepth(1.f);
  glClearColor(0.3f, 0.3f, 0.3f, 0.f);
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.f, 1.f, 1.f, 300.0f);
  std::vector<std::vector<int>> map;
  map.resize(3);
  map[0].resize(3);
  map[1].resize(3);
  map[2].resize(3);
  for (size_t i = 0; i < 3; i++)
  {
    for (size_t j = 0; j < 3; j++)
    {
      map[i][j] = 0;
    }
  }
  map[0][1] = 1;
  bool rotate = true;
  float angle;
  while (window.isOpen())
  {
    Event Event;
    while (window.pollEvent(Event))
    {
      if (Event.type == Event::Closed)
        window.close();
      if ((Event.type == Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
        window.close();

      if ((Event.type == Event::KeyPressed) && (Event.key.code == sf::Keyboard::A)) {
        rotate = !rotate;
      }
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.f, 0.f, -100.f);

    if (rotate) {
      angle = Clock.getElapsedTime().asSeconds();
    }
    //glRotatef(angle * 50, 1.f, 0.f, 0.f);
    glRotatef(angle * 30, 0.f, 1.f, 0.f);
    glRotatef(angle * 90, 0.f, 0.f, 1.f);
    std::vector<Wall> walls = GenerateWalls(map, 30);
    float size = 50.0f;
    gluLookAt(0, 0, 50, 0, 0, 0, 20, 20, 20);
    for (Wall wall : walls)
    {
      glBegin(GL_QUADS);
      glColor3f(1, 0, 1);
      glVertex3f(wall.A.X, wall.A.Y, wall.A.Z);
      glVertex3f(wall.B.X, wall.B.Y, wall.B.Z);
      glVertex3f(wall.C.X, wall.C.Y, wall.C.Z);
      glVertex3f(wall.D.X, wall.D.Y, wall.D.Z);
      glEnd();
    }
    window.display();
  }
  return 0;
}

