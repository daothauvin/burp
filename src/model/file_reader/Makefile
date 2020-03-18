CC = gcc 
CFLAGS = -g -Wall -std=c11  -Wextra -pedantic `pkg-config --cflags glib-2.0`
OBJS = syntax_analyse.o interpreter.o test_file_reader.o
BIN = test_file_reader
LIBS = `pkg-config --libs glib-2.0`

all: clear $(BIN) clean_objs

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) $(LIBS)

clear: # Clear the terminal
	clear

clean_objs: # Clean *.o files
	$(RM) $(OBJS)

clean: # Clean binary files
	$(RM) $(BIN) $(OBJS)
