#include <main.h>

def(int, main, int argc, char ** argv)
  Window * window = interface_window("c with object", 1280, 720);
  vec3 color = body
    0.0,0.0,0.0
  ends
  Mesh * meshes[2] = {
     interface_Box(
       interface_shader(
       "shader/tri.vs",
       "shader/tri.fs"),
       0,0,0.2,0.2
		   ),
     interface_Font(interface_shader("shader/font.vs","shader/font.fs"),
		    L'你',0,720 - 48,1,color)
  };
  window->connect_Mesh(window, meshes, 2);
  window->render(window);
  return 0;
end
