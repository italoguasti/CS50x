all: tp.o automato.o double_hash.o
	@gcc tp.o automato.o double_hash.o -o exe
	@rm -r tp.o automato.o double_hash.o
tp.o: tp.c
	@gcc tp.c -c -Wall
automato.o: automato.c
	@gcc automato.c -c -Wall
double_hash.o: double_hash.c
	@gcc double_hash.c -c -Wall
val:
	@gcc -g -o exeval double_hash.c automato.c tp.c -Wall
valrun: val
	@valgrind --leak-check=full --track-origins=yes -s ./exeval
run:
	@./exe
