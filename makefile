default:
	gcc src/main.c -o out/a.out -I inc -Llib -lGCL
	./out/a.out