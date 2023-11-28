all:
	gcc -Wall -Wextra -O3 `pkg-config --cflags sdl2` -c -o render.o render.c
	gcc -Wall -Wextra -O3 `pkg-config --cflags sdl2` -c -o conway.o conway.c
	gcc render.o conway.o `pkg-config --libs sdl2` -lm -o conway

clean:
	rm -f conway
	rm -f *.o
