statTest: main.c
	gcc main.c -g -lm -o statTest

run: statTest
	./statTest

clean:
	rm *~
