timer: timer.cpp sdlstuff.cpp renderer.h renderer.cpp globalvars.h
	g++ timer.cpp -w -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o timer
