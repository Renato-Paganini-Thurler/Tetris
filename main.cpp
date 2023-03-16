// The graphics library

#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

// Global variables

const int HEIGHT = 20;
const int WIDTH = 10;

int field[HEIGHT][WIDTH] = {0};

// A point with coordinates x and y, with two instances a and b, each one has four values inside
struct Point
{
  int x, y;
} a[4], b[4];

// Seven pieces, each has four elements
int pieces[7][4]{
    1, 3, 5, 7, // I
    2, 4, 5, 7, // Z
    3, 5, 4, 6, // S
    3, 5, 4, 7, // T
    2, 3, 5, 7, // L
    3, 5, 7, 6, // J
    2, 3, 4, 5, // O
};

/*
Piece array has four elements broken into even and odds, applying the piece description to this the pattern of the pieces appear

0: |0|1|
1: |2|3|
2: |4|5|
3: |6|7|

*/

// Verifies the position of the pieces
bool check()
{
  for (int i = 0; i < 4; i++){
    if (a[i].x < 0 || a[i].x >= WIDTH || a[i].y >= HEIGHT){
      return false;}
    else if (field[a[i].y][a[i].x]){
      return false;
    }
  }
  return true;
};

int main()
{

  srand(time(0));

  // Resolution and window name
  RenderWindow window(VideoMode(320, 480), "Tetris");

  // Tiles sprites and textures
  Texture tiles;
  tiles.loadFromFile("src/tiles.png");

  Sprite tile(tiles);
  // Texture size
  tile.setTextureRect(IntRect(0, 0, 18, 18));

  // Tiles variables
  int dx = 0;
  bool rotate = false;
  int colorOption = 1;

  // Time
  float timer = 0;
  float delay = 0.3;

  Clock clock;

  // Main game loop
  while (window.isOpen())
  {
    // Time
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;

    // Events like windows, key presses, frames
    Event e;
    while (window.pollEvent(e))
    {
      if (e.type == Event::Closed)
      {
        window.close();
      }

      // Input control
      if (e.type == Event::KeyPressed)
      {
        if (e.key.code == Keyboard::Up)
        {
          rotate = true;
        }
        else if (e.key.code == Keyboard::Left)
        {
          dx = -1;
        }
        else if (e.key.code == Keyboard::Right)
        {
          dx = 1;
        }
      }
    }

    // Move

    for (int i = 0; i < 4; i++)
    {
      b[i] = a[i];
      a[i].x += dx;
    }

    // This can be inverted
    if (!check())
    {
      for (int i = 0; i < 4; i++)
      {
        a[i] = b[i];
      }
    }

    // Rotate
    
    if (rotate)
    {

      Point centralPoint = a[1];

      for (int i = 0; i < 4; i++)
      {
        int x = a[i].y - centralPoint.y;
        int y = a[i].x - centralPoint.x;
        a[i].x = centralPoint.x - x;
        a[i].y = centralPoint.y + y;
      }
      if (!check())
      {
        for (int i = 0; i < 4; i++)
        {
          a[i] = b[i];
        }
      }
    }

    // Tick and fall
    if (timer > delay)
    {
      for (int i = 0; i < 4; i++)
      {
        b[i] = a[i];
        a[i].y += 1;
      }

      if (!check())
      {
        for (int i = 0; i < 4; i++){
          field[b[i].y][b[i].x] = colorOption;
        }

        colorOption = 1 + rand() % 7;
        //Defines which piece will show 
        int n = rand() % 7;
        for (int i = 0; i < 4; i++)
        {
          // Divide point a into two components
          a[i].x = pieces[n][i] % 2;
          a[i].y = pieces[n][i] / 2;
        }
      }

      timer = 0;
    }

    dx = 0;
    rotate = false;

    // Draw
    window.clear(Color::White);

    for (int i = 0; i < HEIGHT; i++)
    {
      for (int j = 0; j < WIDTH; j++)
      {
        if(field[i][j] == 0) continue;

        tile.setPosition(j*18, i*18);
        window.draw(tile);
      }
    }

    for (int i = 0; i < 4; i++)
    {
      tile.setPosition(a[i].x * 18, a[i].y * 18);
      window.draw(tile);
    }

    window.display();
  }
  return 0;
}
