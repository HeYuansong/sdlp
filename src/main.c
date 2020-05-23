#include <main.h>
int main(){
  Window * window = interface_window("c with object", 1280, 720);
  Mesh * meshes[2] = {
     interface_Box(interface_shader("shader/tri.vs","shader/tri.fs"),
		   0,0,1,1),
     interface_Box(interface_shader("shader/tri.vs","shader/tri.fs"),
		   0.75,0.75,0.5,0.5)
  };
  Mesh * meshes2[1] = {
     interface_Box(interface_shader("shader/tri.vs","shader/tri.fs"),
					   -0.75,-0.75,0.5,0.5)};
  window->connect_Mesh(window, meshes, 2);
  window->connect_Mesh(window, meshes2, 1);
  window->render(window);
  return 0;
}
