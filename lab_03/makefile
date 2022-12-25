CC      := gcc
CCFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion -I inc -g3

SRC := src/
OUT := out/
INC := inc/

.PHONY: clean all

all: app.exe

app.exe: $(OUT)main.o
	$(CC) -o $@ $^

$(OUT)%.o: $(SRC)%.c $(INC)*.h
	if ! [ -d $(OUT) ]; then mkdir $(OUT); fi
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	if [ -d $(OUT) ]; then rm -rf $(OUT); fi
	rm *.exe
	rm *.temp