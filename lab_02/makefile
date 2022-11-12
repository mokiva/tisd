CC      := gcc
CCFLAGS := -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion

app.exe: main.o funcs.o
	$(CC) -o $@ $^

main.o: main.c defines.h structs.h
	$(CC) $(CCFLAGS) -c $<

funcs.o: funcs.c defines.h structs.h
	$(CC) $(CCFLAGS) -c $<

.PHONY: clean

clean:
	rm *.o
	rm app.exe