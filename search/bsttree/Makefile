bst:main.o bst.o
	gcc -o bst main.o bst.o
main.o:main.c bst.h
	gcc -c main.c
bst.o:bst.c bst.h
	gcc -c bst.c
clean:
	rm -f *.o
	rm -f bst
