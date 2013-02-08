CC=gcc
CFLAGS=`pkg-config --cflags gtk+-2.0 opencv` -g 
LDFLAGS=`pkg-config --libs gtk+-2.0 opencv` -lm -lgmp
OBJ=../../src/game.o ../../src/random.o ../../src/graph.o

%.o : %.c
	$(CC) -c $< $(CFLAGS) -o $@

all: game_payoff_test game_p_i_test
	
game_payoff_test: game_payoff_test.o
	$(CC) $< $(OBJ) -o game_payoff_test $(LDFLAGS)
	
game_p_i_test: game_p_i_test.o
	$(CC) $< $(OBJ) -o game_p_i_test $(LDFLAGS)

clean:
	rm *.o game_payoff_test game_p_i_test
