2048console: 2048.cpp modele.cpp
	g++ 2048.cpp modele.cpp -o 2048console

2048interactive: 2048_interactive.cpp modele.cpp
	g++ 2048_interactive.cpp modele.cpp -o 2048interactive -lncurses

2048graphic: 2048_graphic.cpp modele.cpp
	g++ 2048_graphic.cpp modele.cpp -I src/include -L src/lib -o 2048graphic -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2