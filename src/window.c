#include <window.h>
def(static void,createText,wchar_t * s,int line,int size,Window*window)
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

static def(void,wfree,Window*window)
    times(window->mesh_count)
      free(window->mesh[i]->shader);
      free(window->mesh[i]->vertex_array->vertices);
      free(window->mesh[i]->vertex_array);

      free(window->mesh[i]->index_array->indices);
      free(window->mesh[i]->index_array);

      free(window->mesh[i]->texture_array->textures);
      free(window->mesh[i]->texture_array);

      free(window->mesh[i]);
    end
    free(window->mesh);
    SDL_DestroyWindow(window->instance);
    free(window);
    SDL_Quit();
end
  
def(static void, connect_Mesh, Window*window,Mesh ** meshes, unsigned mesh_count)
  Mesh ** mesh = (Mesh**)malloc(sizeof(Mesh**)*(window->mesh_count + mesh_count));
  times(window->mesh_count)
    mesh[i] = window->mesh[i];
  end
  fromto(window->mesh_count, window->mesh_count + mesh_count)
    mesh[i] = meshes[i - window->mesh_count];
  end
  free(meshes);
  if(window->mesh_count != 0) body
    free(window->mesh);
    window->mesh = NULL;
  end
  window->mesh_count = window->mesh_count + mesh_count;
  window->mesh = mesh;
end

def(static void, render , Window * window)
  window->exit_state = 1;
  when(window->exit_state)
    window->event(window);
    glClear( GL_COLOR_BUFFER_BIT );
    glClearColor(1.0, 1.0, 1.0, 1.0);
    times(window->mesh_count)
      Mesh * mesh = window->mesh[i];
      mesh->render(mesh);
    end
    SDL_GL_SwapWindow(window->instance);
    SDL_Delay(1000/window->frame);
  end
  window->free(window);
end

def(static void, event ,Window * window)
  SDL_Event event;
  when(SDL_PollEvent(&event))
    cond(event.type == SDL_WINDOWEVENT_CLOSE)
      cond(window->instance)
        SDL_DestroyWindow(window->instance);
        window->instance = NULL;
      end
    end
    cond(event.type == SDL_KEYDOWN)
      cond(event.key.keysym.sym == SDLK_ESCAPE)
        window->exit_state = 0;
      end
    end
    esif(event.type == SDL_TEXTINPUT)
        wchar_t s[1024];
        swprintf(s, 1024, L"%s", event.text.text);
        createText(s,3,48,window);
    end
    esif(event.type == SDL_QUIT)
      window->exit_state = 0;
    end
  end
end

def(Window * , interface_window ,char * name, int w, int h)
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

  setlocale(LC_ALL, "");

  Window * window = (Window*)malloc(sizeof(Window));
  window->instance = sdlWindow;
  window->event = event;
  window->render = render;
  window->connect_Mesh = connect_Mesh;
  window->frame = 120;
  window->mesh_count = 0;
  window->free = wfree;
  return window;
end
