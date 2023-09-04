build:
	gcc -Wall -std=c99 \
	./src/*.c \
	-o renderer \
	-I /opt/homebrew/Cellar/sdl2/2.28.2/include/ \
	-L /opt/homebrew/Cellar/sdl2/2.28.2/lib/ \
	-l SDL2 \
	-lm

run:
	./renderer

clean:
	rm ./renderer