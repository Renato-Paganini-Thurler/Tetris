// The graphics library
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

// Global variables //

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

Pieces array has four elements broken into even and odds, applying the piece description to this the pattern of the pieces appear

0: |0|1|
1: |2|3|
2: |4|5|
3: |6|7|

*/

// Verifies the position of the pieces
bool check()
{
  for (int i = 0; i < 4; i++)
  {
    if (a[i].x < 0 || a[i].x >= WIDTH || a[i].y >= HEIGHT)
    {
      return false;
    }
    else if (field[a[i].y][a[i].x])
    {
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

  Texture tframe;
  tframe.loadFromFile("src/frame.png");

  Texture tbg;
  tbg.loadFromFile("src/background.png");

  // Load the textures into the sprites

  Sprite tile(tiles);
  Sprite backgorund(tbg);
  Sprite frame(tframe);

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

    //Pieces fall faster
    if (Keyboard::isKeyPressed(Keyboard::Down)){
      delay = 0.05;
    }

    for (int i = 0; i < 4; i++)
    {
      b[i] = a[i];
      a[i].x += dx;
    }

    // Each value is stored on point b
    if (!check())
    {
      for (int i = 0; i < 4; i++)
      {
        a[i] = b[i];
      }
    }

    // Rotate, by transforming coordinates//

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

    // Tick and fall //

    if (timer > delay)
    {
      for (int i = 0; i < 4; i++)
      {
        b[i] = a[i];
        a[i].y += 1;
      }

      if (!check())
      {
        for (int i = 0; i < 4; i++)
        {
          field[b[i].y][b[i].x] = colorOption;
        }

        colorOption = 1 + rand() % 7;
        // Defines which piece will show
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

    // Check
    int k = HEIGHT - 1;
    for (int i = HEIGHT - 1; i > 0; i--)
    {
      int count = 0;
      for (int j = 0; j < WIDTH; j++)
      {
        if (field[i][j])
        {
          count++;
        }
        field[k][j] = field[i][j];
      }
      if (count < WIDTH)
      {
        k--;
      }
    }

    dx = 0;
    rotate = false;
    delay = 0.3;

    // Draw
    window.clear(Color::White);
    window.draw(backgorund);

    for (int i = 0; i < HEIGHT; i++)
    {
      for (int j = 0; j < WIDTH; j++)
      {
        if (field[i][j] == 0)
          continue;
        tile.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
        tile.setPosition(j * 18, i * 18);
        tile.move(28, 31); // offset
        window.draw(tile);
      }
    }

    for (int i = 0; i < 4; i++)
    {
      tile.setTextureRect(IntRect(colorOption * 18, 0, 18, 18));
      tile.setPosition(a[i].x * 18, a[i].y * 18);
      tile.move(28, 31); // offset
      window.draw(tile);
    }
    window.draw(frame);
    window.display();
  }
  return 0;
}
