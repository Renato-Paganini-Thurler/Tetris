// The graphics library

#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
  // Window and resolution
  RenderWindow window(VideoMode(320, 480), "Tetris");
  while (window.isOpen())
  {
    //Closes the window if pollEvent happens
    Event e;
    while(window.pollEvent(e)){
      if(e.type == Event::Closed){
        window.close();
      }
    }
    window.clear(Color::White);
  }

  return 0;
}