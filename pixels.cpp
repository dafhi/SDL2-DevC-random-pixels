/* -- Dev-C++     -lmingw32 -lSDL2main -lSDL2
*/

#include <SDL.h>

#include <limits>

#define uint   unsigned int
#define rnd    drand()

double drand() {
	static uint a = 0, b = 0;
	const uint max = std::numeric_limits<unsigned int>::max();
	a *= a;
	a ^= b;
	b += 1;
	return (double)a / max;
}

uint rgb(int r, int g, int b){
   return r << 16 | g << 8 | b;
}
   
/* Random pixEls */
int main(int argc, char *argv[]){
   SDL_Window *window;
   SDL_Renderer *renderer;
   SDL_Surface*  buf, surface;
   SDL_Event event;
   SDL_Rect r;
   
   r.w = 640;
   r.h = 360;
      
   window = SDL_CreateWindow("SDL_CreateTexture",
                  SDL_WINDOWPOS_UNDEFINED,
                  SDL_WINDOWPOS_UNDEFINED,
                  r.w, r.h,
                  SDL_WINDOW_RESIZABLE);
      
   renderer = SDL_CreateRenderer(window, -1, 0);
   
   bool quit = false;
   
   SDL_SetRenderTarget(renderer, NULL);
//   while (!quit) {
      
      SDL_PollEvent(&event);
      
      switch (event.type) {
      case SDL_QUIT:
         quit = true;
         
      case SDL_WINDOWEVENT:
         switch (event.window.event) {
         case SDL_WINDOWEVENT_RESIZED:
            ;
         }
         
      case SDL_KEYDOWN:
         switch( event.key.keysym.sym ){
         case SDLK_ESCAPE:
            quit = true;
         }
      }
      
      //SDL_RenderClear(renderer);
      buf = SDL_GetWindowSurface(window);
      
      int pitchBy = buf->pitch / 4;
      uint *pixels = (uint *)buf->pixels;
      
      SDL_LockSurface(buf);
         for (int j=0; j<buf->h; j++){
            int y_pitch = j * pitchBy;
            for (int i=0; i<buf->w; i++) {
               pixels[y_pitch+i] = rgb(rnd*255,rnd*255,rnd*255);
            }
         }
      SDL_UnlockSurface(buf);
      SDL_UpdateWindowSurface(window);
      SDL_Delay(2000);
//   }
   SDL_DestroyRenderer(renderer);
   SDL_Quit();
   return 0;
}
