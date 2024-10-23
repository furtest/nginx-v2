CC := clang


main: main.o sockets.o
	$(CC) $^ -o $@

main.o: main.c main.h sockets.h	
	$(CC) -c $<

sockets.o: sockets.c sockets.h
	$(CC) -c $<
