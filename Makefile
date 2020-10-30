run: build
	./tetribit

build: tetribit.c
	gcc tetribit.c -o tetribit -lm -Wall -g

clean:
	rm -f tetribit
