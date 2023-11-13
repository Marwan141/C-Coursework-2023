COMPILER=gcc
MAIN = drawing.c
OBJ = drawing.o 

%.o: %.c
	$(COMPILER) -c -o $@ $<

drawing: $(OBJ)
	$(COMPILER) -o $@ $^ 

.PHONY: clean run

clean:
	rm -f $(OBJ) drawing

run: drawing
	./drawing | java -jar drawapp-3.0.jar