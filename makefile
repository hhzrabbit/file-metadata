statTest: main.c
	gcc main.c -g -o statTest

run: statTest
	./statTest

clean:
	rm *~
