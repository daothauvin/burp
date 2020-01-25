CC = gcc
CFLAGS = -g -Wall -std=c11 # -Wextra -pedantic
OBJS = main.o
BIN = burp

all: clear $(BIN) clean_objs
	
$(BIN): $(OBJS)

clear: # Clear the terminal
	clear
	
clean_objs: # Clean *.o files
	$(RM) $(OBJS)

clean: # Clean binary files
	$(RM) $(BIN) $(OBJS)
