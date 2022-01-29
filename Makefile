GCC = gcc -Wall 

all: tree

tree: tree.c tree.h 
	$(GCC) $^ -o $@

clean:
	rm -rf *.o tree