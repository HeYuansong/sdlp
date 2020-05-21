CC = gcc
LIBSDIR = C:/Users/18742/Documents/sdlp/box/libs
CFLAGS = -g -Wall -mwindows
INC = -I $(LIBSDIR)/SDL2/include -I ../include -I $(LIBSDIR)/GLEW/include

TARGET = ../build/app.exe
SRCS =  main.c  \
	window.c\
	mesh.c  \
	shader.c\
	box.c
OBJS = $(SRCS:.c=.o)
LIBS = -L $(LIBSDIR)/SDL2/lib -L $(LIBSDIR)/GLEW/lib/Release/x64 -lSDL2main -lSDL2 -lopengl32 -lglew32
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)
%.o:%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<
clean:
	rm -rf $(TARGET) $(OBJS)
