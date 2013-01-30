CC=gcc
CFLAGS=`pkg-config --cflags gtk+-2.0 opencv` -g 
LDFLAGS=`pkg-config --libs gtk+-2.0 opencv` -lm -lgmp
OBJ=../../src/random.o

%.o : %.c
	$(CC) -c $< $(CFLAGS) -o $@

all: bool_test int_test
	
bool_test: random_boolean_test.o
	$(CC) $< $(OBJ) -o bool_test $(LDFLAGS)

int_test: random_integer_test.o
	$(CC) $< $(OBJ) -o int_test $(LDFLAGS)

clean:
	rm *.o bool_test int_test
