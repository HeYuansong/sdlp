#include <window.h>
static void connect_Mesh(Window*window,Mesh ** meshes, unsigned mesh_count){
  Mesh ** mesh = (Mesh**)malloc(sizeof(Mesh**)*(window->mesh_count + mesh_count));
  for(int i = 0;i<window->mesh_count;i++)
    mesh[i] = window->mesh[i];
  for(int i = window->mesh_count;i<window->mesh_count + mesh_count;i++)
    mesh[i] = meshes[i - window->mesh_count];
  if(window->mesh_count != 0)
    free(window->mesh);
  window->mesh_count = window->mesh_count + mesh_count;
  window->mesh = mesh;
}
static void render(Window * window){
  window->exit_state = 1;
  while(window->exit_state){
    window->event(window);
    glClear( GL_COLOR_BUFFER_BIT );
    glClearColor(1.0, 1.0, 1.0, 1.0);
    for(int i = 0;i < window->mesh_count;i++){
      Mesh * mesh = window->mesh[i];
      mesh->render(mesh);
    }
    SDL_GL_SwapWindow(window->instance);
    SDL_Delay(1000/window->frame);
  }
  SDL_DestroyWindow(window->instance);
  SDL_Quit();
}
static void event(Window * window){
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch(event.type){
    case SDL_WINDOWEVENT_CLOSE:{
      if(window->instance){
      	SDL_DestroyWindow(window->instance);
      	window->instance = NULL;
      }
      break;
    }
    case SDL_KEYDOWN:{
      switch(event.key.keysym.sym){
        case SDLK_ESCAPE:{
	        window->exit_state = 0;
	        break;
        }
      }
      break;
    }
    case SDL_QUIT:{
        window->exit_state = 0;
        break;
      }
    }
  }
}
Window * interface_window(char * name, int w, int h){
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
  SDL_Window * sdlWindow = SDL_CreateWindow( name,
					     SDL_WINDOWPOS_UNDEFINED,
					     SDL_WINDOWPOS_UNDEFINED,
					     w,
					     h,
					     SDL_WINDOW_OPENGL|
					     SDL_WINDOW_SHOWN |
					     SDL_WINDOW_RESIZABLE);
  SDL_GL_CreateContext( sdlWindow );
  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if( glewError != GLEW_OK )
    printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
  if( SDL_GL_SetSwapInterval( 1 ) < 0 )			
    printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
  glViewport(0, 0, w, h);
  Window * window = (Window*)malloc(sizeof(Window));
  window->instance = sdlWindow;
  window->event = event;
  window->render = render;
  window->connect_Mesh = connect_Mesh;
  window->frame = 120;
  window->mesh_count = 0;
  return window;
}