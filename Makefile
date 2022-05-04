all :
	gcc -o ./bin/logMin ./src/main.c ./src/logicMinimization.c
	./bin/logMin
dbg :
	gcc -g -o ./bin/debug ./src/main.c ./src/logicMinimization.c
	gdb ./bin/debug