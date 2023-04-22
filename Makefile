BIN= analyseur
C= figures
U= utils_lex

all: $(BIN).y $(BIN).l $(C).c $(U).c
	$(CC) -c $(C).c -o $(C).o
	$(CC) -c $(U).c -o $(U).o
	bison -d -g $(BIN).y
	dot -Tpng $(BIN).dot -o $(BIN).png
	flex -d $(BIN).l
	$(CC) -c lex.yy.c -o lex.yy.o
	$(CC) -c $(BIN).tab.c -o $(BIN).tab.o
	$(CC) -o $(BIN).bin lex.yy.o $(BIN).tab.o $(C).o $(U).o -lm

clean:
	rm -fv $(U).o $(C).o $(BIN).bin $(BIN).tab.h $(BIN).tab.c lex.yy.c lex.yy.o $(BIN).tab.o lex.backup $(BIN).dot $(BIN).png $(BIN).output *.svg *~ 