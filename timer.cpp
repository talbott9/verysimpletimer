#include "sdlstuff.cpp"
#include "globalvars.h"
#include "renderer.h"
#include "renderer.cpp"
#include "media.cpp"

int timeTicks = 60*60*30;
int otherTick = 0;
int hms[3];
LTexture gText;
SDL_Color bgColor = {0, 0, 0};
SDL_Rect bg = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
SDL_Color textColor = {255, 255, 255};
int main(int argv, char** args) {
  if(!init()) {
    printf( "Failed to initialize!\n" );
  }
  loadFont(60);

  bool quit = false;
  SDL_Event e;

  SDL_SetWindowResizable(gWindow, SDL_TRUE);
  
  while(!quit) {
    while( SDL_PollEvent( &e ) != 0 ) {
      //User requests quit
      if( e.type == SDL_QUIT )
	quit = true;
    }
    Uint32 starting_tick = SDL_GetTicks();

    int mouseX, mouseY;
    bool mouseLeft, mouseRight, mouseCenter;
    mouseLeft = SDL_GetMouseState(&mouseX, &mouseY) == 1;
    mouseCenter = SDL_GetMouseState(&mouseX, &mouseY) == 2;
    mouseRight = SDL_GetMouseState(&mouseX, &mouseY) == 4;
    if(mouseLeft)
      timeTicks += 60*2;

    if(mouseRight)
      timeTicks -= 60*2;

    if(mouseCenter)
      timeTicks = 60*60*30+1*60;

    if(otherTick % 60 == 0) {


      std::string fullString;
      std::string tstr[3];
    
      //if(timeTicks < 0)
      //  timeTicks = 0;
      if(timeTicks > 0) {
	fullString += " ";
	textColor = {255, 255, 255};
      } else {
	fullString += "-";
	textColor = {255, 0, 0};
      }

      int fticks = abs(timeTicks);

      hms[0] = fticks/3600/60;
      fticks -= 3600*60*(hms[0]);
      hms[1] = fticks/3600;
      fticks -= 3600*(hms[1]);
      hms[2] = fticks/60;


      SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
      SDL_RenderFillRect(gRenderer, &bg);

      for(int i= 0; i < 3; i++) {
	tstr[i] = std::to_string(hms[i]);
	if(tstr[i].size() < 2)
	  fullString += "0";
	fullString += tstr[i];
	if(i != 2)
	  fullString += ":";
      }
      gText.loadFromRenderedText(fullString, textColor, 0, gFont);
      gText.render(10,0);
      SDL_RenderPresent(gRenderer);
      SDL_RenderClear(gRenderer);
    }

    timeTicks--;
    otherTick++;
    if( (1000/fps) > SDL_GetTicks() - starting_tick )
      SDL_Delay(1000/fps - (SDL_GetTicks() - starting_tick));
    frame_time = SDL_GetTicks()-starting_tick;
    calcFPS = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
      
  }
  
  close();
  return 0;
}
