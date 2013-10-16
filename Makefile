default: run

run: fork.c
	gcc -o fork fork.c
	./fork
clean: fork
	rm fork

