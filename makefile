CC=gcc
CFLAGS=-I.
DEPS = setup.h
OBJ = setup.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

setup: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean run

clean:
	rm -f $(OBJ) setup

run: setup
	./setup | java -jar drawapp-3.0.jar