CC = cc
CFLAGS = -g -Wall
TARGET = ../build/app
SRCS =  main.c  \
	window.c\
	mesh.c  \
	shader.c\
	box.c\
	font.c
OBJS = $(SRCS:.c=.o)

LIBSDIR = ../libs
INC = -I$(LIBSDIR)/GLEW/include \
      -I$(LIBSDIR)/SDL2/include \
      -I$(LIBSDIR)/FREETYPE/include \
      -I../include
LIBS = -L$(LIBSDIR)/GLEW/lib -lGLEW \
       -L$(LIBSDIR)/SDL2/lib -lSDL2 \
       -L$(LIBSDIR)/FREETYPE/lib -lfreetype \
       -lGL
LDCONFIG = -Wl, \
       -rpath=$(LIBSDIR)/GLEW/lib, \
       -rpath=$(LIBSDIR)/SDL2/lib, \
       -rpath=$(LIBSDIR)/FREETYPE/lib
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(LDCONFIG) $(OBJS) -o $(TARGET) $(LIBS)
%.o:%.c  
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<
clean:
	rm -rf $(TARGET) $(OBJS)
