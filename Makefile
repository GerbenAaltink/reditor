all: build run

build:
	gcc redit.c -o redit -lm 

run:
	./redit
