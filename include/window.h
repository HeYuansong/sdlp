#include <head.h>
#include <mesh.h>
#include <box.h>
#ifndef _WINDOW_
#define _WINDOW_
interface(Window){
  SDL_Window * instance;
  char exit_state;
  short frame;
  unsigned mesh_count;
  Mesh ** mesh;
  void(*event)(Window*);
  void(*render)(Window*);
  void(*connect_Mesh)(Window*, Mesh**, unsigned);
};
Window * interface_window(char * name , int w, int h);
#endif
