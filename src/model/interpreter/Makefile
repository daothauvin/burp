CC = gcc `pkg-config --cflags --libs glib-2.0`
CFLAGS = -g -Wall -std=c11 # -Wextra -pedantic
OBJS = interpreter.o test_interpreter.o 
BIN = test_interpreteur

all: clear $(BIN) clean_objs
	
$(BIN): $(OBJS)

clear: # Clear the terminal
	clear
	
clean_objs: # Clean *.o files
	$(RM) $(OBJS)

clean: # Clean binary files
	$(RM) $(BIN) $(OBJS)
