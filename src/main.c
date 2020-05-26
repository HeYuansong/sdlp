#include <main.h>

def(int, main, int argc, char ** argv)
  Window * window = interface_window("c with object", 1280, 720);
  Mesh * meshes[2] = body(
     interface_Box(
     interface_shader(
     "shader/tri.vs",
     "shader/tri.fs"),
     0,0,1,1),
     interface_Box(
     interface_shader(
     "shader/tri.vs",
     "shader/tri.fs"),
     0.75,0.75,0.5,0.5)
  );
  Mesh * meshes2[1] = body
     interface_Font(
     interface_shader(
     "shader/font.vs",
     "shader/font.fs"),
     L'嗨',
     100,
     100,
     20,
     body
     0.0,
     0.0,
     0.0
     end)
  ends
  window->connect_Mesh(window, meshes, 2);
  window->connect_Mesh(window, meshes2, 1);
  window->render(window);
  return 0;
end
