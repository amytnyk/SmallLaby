// SmallLabySfml.cpp : main project file.

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "ClientModel.h"
#include "SmallLabySfml.h"

using namespace sf;
RenderWindow window(VideoMode(800, 700), "First sfml program!");

bool IsPlayerOnField(int x, int y, const std::vector<Player> &players, int player_id, bool& is_me)
{
  for (size_t k = 0; k < players.size(); k++)
  {
    if (players[k].X == y && players[k].Y == x)
    {
      is_me = player_id == players[k].Id;
      return true;
    }
  }
  return false;
}

bool MonsterIsOnField(int x, int y, const std::vector<Monster> &monsters)
{
  for (size_t i = 0; i < monsters.size(); i++)
  {
    if (monsters[i].X == y && monsters[i].Y == x)
    {
      return true;
    }
  }
  return false;
}

bool IsGoldOnField(int x, int y, const std::vector<Item> &items)
{
  for (const Item& item : items)
  {
    if (item.Type == ItemType::Gold && item.X == y && item.Y == x)
    {
      return true;
    }
  }
  return false;
}

void DrawPanel(int gold, double speed)
{
  Sprite sprite;
  Texture texture;
  texture.loadFromFile("Images/coins.png");
  sprite.setTexture(texture);
  auto size = texture.getSize();
  sprite.setScale(50.0f / size.x, 50.0f / size.y);
  sprite.setPosition(600, 0);
  window.draw(sprite);
  Font font;
  font.loadFromFile("Raleway-Italic.ttf");
  Text text;
  text.setFont(font);
  text.setString(std::to_string(gold));
  text.setCharacterSize(50);
  text.setColor(Color::Red);
  text.setPosition(700, 0);
  window.draw(text);
  text.setString(std::to_string((int)speed));
  text.setPosition(700, 60);
  window.draw(text);
}

/*void DrawC(bool IsConected)
{
  RectangleShape rect;
  rect.setPosition(0, 500);
  rect.setFillColor(Color::Red);
  rect.setSize(Vector2f(300.0f, 50.0f));
  window.draw(rect);
  rect.setPosition(500, 500);
  rect.setFillColor(Color::Red);
  window.draw(rect);
  Font font;
  font.loadFromFile("Raleway-Italic.ttf");
  Text text;
  text.setFont(font);
  text.setString("Connect");
  text.setCharacterSize(50);
  text.setColor(Color::Yellow);
  text.setPosition(0, 500);
  window.draw(text);
  text.setString("Disconnect");
  text.setPosition(500, 500);
  window.draw(text);
}
*/

void DrawMap(
  const std::vector<std::vector<Terrain>> &map,
  const std::vector<Player> &players, 
  const std::vector<Monster> &monsters,
  const std::vector<Item> &items,
  int player_id)
{
  float s = 30.0f;
  Texture player_texture;
  player_texture.loadFromFile("Images/player.bmp");
  Texture gold_texture;
  gold_texture.loadFromFile("Images/gold1.png");
  Texture enemy_texture;
  enemy_texture.loadFromFile("Images/m1.bmp");
  Texture my_texture;
  my_texture.loadFromFile("Images/aze1.bmp");
  Texture wall_texture;
  wall_texture.loadFromFile("Images/mud.bmp");
  Texture road_texture;
  road_texture.loadFromFile("Images/road.bmp");
  for (int i = 0; i < map.size(); i++)
  {
    for (int j = 0; j < map[i].size(); j++)
    {
      Sprite sprite;
      Vector2u size;
      bool is_me;
      if (IsPlayerOnField(i, j, players, player_id, is_me))
      {
        if (is_me)
        {
          sprite.setTexture(my_texture);
          size = my_texture.getSize();
        }
        else
        {
          sprite.setTexture(player_texture);
          size = player_texture.getSize();
        }
      }
      else if (MonsterIsOnField(i, j, monsters))
      {
        sprite.setTexture(enemy_texture);
        size = enemy_texture.getSize();
      }
      else
      {
        switch (map[i][j])
        {
        case Terrain::Road:
        {
          sprite.setTexture(road_texture);
          size = road_texture.getSize();
          break;
        }
        case Terrain::Wall:
        {
          sprite.setTexture(wall_texture);
          size = wall_texture.getSize();
          break;
        }
        }
      }
      sprite.setScale(s / size.x, s / size.y);
      sprite.setPosition(j * s, i * s);
      window.draw(sprite);

      if (IsGoldOnField(i, j, items))
      {
        Sprite sprite;
        sprite.setTexture(gold_texture);
        size = gold_texture.getSize();
        sprite.setScale(s / size.x, s / size.y);
        sprite.setPosition(j * s, i * s);
        window.draw(sprite);
      }
    }
  }
}

bool IsOnSquare(int x, int y, int s, int s2, int yourX, int yourY)
{
  if (yourY < y + s2 && yourY > y && yourX > x && yourX < x + s)
    return true;
  else
    return false;
}

int main(array<System::String ^> ^args)
{
  bool connected = false;
  ClientModel client_model;
  int player_id = 0;
  //player_id = client_model.AddPlayer("alex");
  int w = client_model.GetWidth();
  int h = client_model.GetHeight();
  auto map = client_model.GetMap();
  auto players = client_model.GetPlayers();
  while (window.isOpen())
  {
    Event event;
    while (window.pollEvent(event))
    {
      if (event.type == Event::Closed)
      {
        window.close();
        continue;
      }
      if (Keyboard::isKeyPressed(Keyboard::Escape))
      {
        window.close();
        continue;
      }
      Vector2i position = Mouse::getPosition();
      if (Mouse::isButtonPressed(Mouse::Button::Left))
      {
        /*if (!connected && IsOnSquare(0, 500, 300, 50, position.x, position.y))
        {//Connect
          player_id = client_model.AddPlayer("alex");
          connected = true;
        }
        if (connected && IsOnSquare(500, 500, 300, 50, position.x, position.y))
        {//Disconnect
          client_model.RemovePlayer(player_id);
          connected = false;
        }*/
        if (!connected)
        {//Connect
          player_id = client_model.AddPlayer("alex");
          connected = true;
        }
        else if (connected)
        {//Disconnect
          client_model.RemovePlayer(player_id);
          connected = false;
        }
      }
      if (connected)
      {
        if (Keyboard::isKeyPressed(Keyboard::Down))
          client_model.SetMoveStrategy(player_id, MoveStrategy::MoveDown);
        if (Keyboard::isKeyPressed(Keyboard::Up))
          client_model.SetMoveStrategy(player_id, MoveStrategy::MoveUp);
        if (Keyboard::isKeyPressed(Keyboard::Left))
          client_model.SetMoveStrategy(player_id, MoveStrategy::MoveLeft);
        if (Keyboard::isKeyPressed(Keyboard::Right))
          client_model.SetMoveStrategy(player_id, MoveStrategy::MoveRight);
      }
    }
    window.clear(Color(0, 200, 0, 200));
    auto players = client_model.GetPlayers();
    auto monsters = client_model.GetMonsters();
    auto items = client_model.GetItems();
    DrawMap(map, players, monsters, items, player_id);
    //DrawC(connected);
    if (connected)
    {
      int gold = client_model.Gold(player_id);
      double speed = client_model.Speed(player_id);
      DrawPanel(gold, speed);
    }
    window.display();
  }
  
  if (connected)
  {
    client_model.RemovePlayer(player_id);
    client_model.Close();
  }
  return 0;
}
