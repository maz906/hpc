CC = gcc
CFLAGS = -Wall -Ofast -fopenmp
ROOT = .
INCLUDE_PATH = $(ROOT)/include
LIBRARY_PATH = $(ROOT)/lib
SOURCE = $(ROOT)/src
TEST = $(ROOT)/test
BIN = $(ROOT)/bin
HEADERS = qsort.h
LIBRARIES = 
all: qsort test clean

qsort: 
	$(CC) $(CFLAGS) -c -o $(BIN)/qsort $(SOURCE)/qsort.c -I$(INCLUDE_PATH) -L$(LIBRARY_PATH) $(addprefix -l, $(LIBRARIES))

test: $(BIN)/qsort.o
	$(CC) $(CFLAGS) -o $(BIN)/test_qsort $(TEST)/test.c $(BIN)/qsort.o -I$(INCLUDE_PATH) -L$(LIBRARY_PATH) $(addprefix -l, $(LIBRARIES))

$(BIN)/%.o : $(SOURCE)/%.c $(addprefix $(INCLUDE_PATH)/, $(HEADERS))
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCLUDE_PATH) -L$(LIBRARY_PATH) $(addprefix -l, $(LIBRARIES))

clean:
	rm -f $(BIN)/*.o
