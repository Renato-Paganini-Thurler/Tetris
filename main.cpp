// The graphics library
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

//Global variables

const int HEIGHT = 20;
const int WIDTH = 10;

int field[HEIGHT][WIDTH] = {0};

//A point with coordinates x and y, with two instances a and b, each one has four values inside
struct Point
{int x , y;} a[4], b[4];


//Seven pieces, each has four elements
int pieces[7][4]{
  1,3,5,7, //I
  2,4,5,7, //Z
  3,5,4,6, //S
  3,5,4,7, //T
  2,3,5,7, //L
  3,5,7,6, //J
  2,3,4,5, //O
};

/*
Piece array has eight elements broken into even and odds, applying the piece description to this the pattern of the pieces appear

|0|1|
|2|3|
|4|5|
|6|7|
*/


int main()
{
  //Resolution and window name
  RenderWindow window(VideoMode(320, 480), "Tetris");
  
  //Tiles sprites and textures
  Texture tiles;
  tiles.loadFromFile("src/tiles.png");

  Sprite tile(tiles);
  //Texture size
  tile.setTextureRect(IntRect(0,0,18,18));

  while (window.isOpen())
  {
  
  //Close window
    Event e;
    while(window.pollEvent(e)){
      if(e.type == Event::Closed){
        window.close();
      }
    }
    window.clear(Color::White);
    window.draw(tile);
    window.display();
  }
  return 0;
}