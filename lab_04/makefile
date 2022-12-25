CC      := gcc
CCFLAGS := -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion -I inc
UFLAGS  := -lcheck -lpthread -lrt -lm -lsubunit

SRC := src/
OUT := out/
INC := inc/
UNT := unit_tests/

.PHONY: clean debug func unit all

all: app.exe #unit_tests.exe

app.exe: $(OUT)main.o
	$(CC) -o $@ $^

#unit_tests.exe: $(OUT)check_funcs.o $(OUT)funcs.o
#	$(CC) -o $@ $^ $(UFLAGS)

$(OUT)%.o: $(SRC)%.c $(INC)*.h
	if ! [ -d $(OUT) ]; then mkdir $(OUT); fi
	$(CC) $(CCFLAGS) -o $@ -c $<

#$(OUT)%.o: $(UNT)%.c $(INC)*.h
#	if ! [ -d $(OUT) ]; then mkdir $(OUT); fi
#	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	if [ -d $(OUT) ]; then rm -rf $(OUT); fi
	rm *.exe
	rm *.temp

#debug: CCFLAGS += -g3
#debug: app.exe

#func:
#	./func_tests/scripts/func_tests.sh

#unit: unit_tests.exe
#unit:
#	./unit_tests.exe
