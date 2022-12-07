default: http.o
	gcc -O3 src/server.c obj/http.o -o out/server -I inc -L lib -lGCL
	./out/server

http.o:
	gcc -O3 -c src/http.c -o obj/http.o

debug:
	gcc -g src/server.c -o out/server -I inc -L lib -lGCL
	gdb out/server