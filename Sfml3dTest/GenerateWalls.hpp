#pragma once
#include "GenerateWall.hpp"
#include <vector>

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