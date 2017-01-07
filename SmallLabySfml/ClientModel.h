#pragma once
#include <memory>
#include <vector>
#include <string>

enum class Terrain
{
  Wall,
  Road
};

enum class MoveStrategy
{
  MoveLeft,
  MoveRight,
  MoveUp,
  MoveDown,
  MoveRandom,
  StandStill
};

enum class ItemType
{
  Gold,
  Bonus,
  Exit,
  Unknown
};

struct Item
{
public:
  int X;
  int Y;
  ItemType Type;
};

struct Player
{
public:
  int X;
  int Y;
  int Id;
};

struct Monster
{
public:
  int X;
  int Y;
};

class ClientModel
{
private:
  struct PrivateModel;

  std::unique_ptr<PrivateModel> _model_impl;

  ClientModel(const ClientModel&);
  ClientModel& operator=(const ClientModel&);

public:
  ClientModel();
  ~ClientModel();
  int GetWidth();
  int GetHeight();
  int AddPlayer(std::string name);
  void SetMoveStrategy(int player_id, MoveStrategy movestrategy);
  std::vector<std::vector<Terrain>> GetMap();
  void RemovePlayer(int player_id);
  void Close();
  std::vector<Player> GetPlayers();
  std::vector<Monster> GetMonsters();
  std::vector<Item> GetItems();
  double Speed(int player_id);
  int Gold(int player_id);
};

