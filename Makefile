slush: slush.o input.o action.o builtins.o variables.o
	gcc -o slush slush.o input.o action.o builtins.o variables.o && rm *.o

slush.o: slush.c
	gcc -o slush.o -c slush.c

input.o: input.c
	gcc -o input.o -c input.c

action.o: action.c
	gcc -o action.o -c action.c

builtins.o: builtins.c
	gcc -o builtins.o -c builtins.c

variables.o: variables.c
	gcc -o variables.o -c variables.c