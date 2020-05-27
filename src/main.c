#include <main.h>
static def(void,createText,wchar_t * s,int line,int size,Window*window)
  unsigned length = 0;
  when(1)
    if(s[length] == L'\0')
      break;
    length++;
  end
  Mesh ** meshes = (Mesh**)malloc(sizeof(Mesh*)*length);
  vec3 color = body
    0.0,0.0,0.0
  ends
  times(length)
    meshes[i] = interface_Font(
       interface_shader("shader/font.vs","shader/font.fs"),
       s[i],size * i,720 - size * line, size, color);
  end
  window->connect_Mesh(window, meshes, length);
end
def(int, main, int argc, char ** argv)

Window * window = interface_window("c with object", 1280, 720);
createText(L"你好世界，这是第一个freetype程序", 1, 48, window);
createText(L"你好世界，这是第一个程序，使用OPENGL渲染", 2, 48, window);
window->render(window);
return 0;

end
