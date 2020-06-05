#include <main.h>

def(int, main, int argc, char ** argv)

Window * window = interface_window("c with object", 1280, 720);
window->render(window);
return 0;

end
