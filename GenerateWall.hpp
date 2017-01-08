#pragma once
#include "Wall.hpp"

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