# Tetris

After I saw the tutorials of FamTrinli, I decided to improve my understanding of classic games by following his tutorials, but modifying his projects to my tastes.


#How to compile 

The SFML libary is essential to this project as well MinGW

https://www.youtube.com/watch?v=rZE700aaT5I&ab_channel=BoostMyTool

//Adding the library to the project
g++ -c main.cpp -I"C:\Program Files\SFML-2.5.1\include"
g++ main.o -o main -L"C:\Program Files\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system
.\main

//Static linking

g++ -c main.cpp -I"C:\Program Files\SFML-2.5.1\include" -DSFML_STATIC
g++ main.o -o main -L"C:\Program Files\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

