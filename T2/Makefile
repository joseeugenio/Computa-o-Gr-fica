CC = gcc

all:
	export LIBGL_ALWAYS_SOFTWARE=1
	export MESA_GL_VERSION_OVERRIDE=3.3
	export MESA_GLSL_VERSION_OVERRIDE=330
	$(CC) -Wall -Wextra -Wpedantic -O0 -g3 main.c -lglut -lGLU -lGL -o moderngl_hello_world

clean:
	rm moderngl_hello_world
