CC=gcc
CFLAGS=`pkg-config --cflags gtk+-2.0 opencv` -g 
LDFLAGS=`pkg-config --libs gtk+-2.0 opencv` -lm -lgmp
OBJ= ../../src/graph.o
PROGS=bipartite_graph_test complete_graph_test cycle_graph_test grid_graph_test uniform_tree_test

%.o : %.c
	$(CC) -c $< $(CFLAGS) -o $@

all: $(PROGS)
	
bipartite_graph_test : bipartite_graph_test.o
	$(CC) $< $(OBJ) -o $@ $(LDFLAGS)
	
complete_graph_test : complete_graph_test.o
	$(CC) $< $(OBJ) -o $@ $(LDFLAGS)
	
cycle_graph_test : cycle_graph_test.o
	$(CC) $< $(OBJ) -o $@ $(LDFLAGS)
	
grid_graph_test : grid_graph_test.o
	$(CC) $< $(OBJ) -o $@ $(LDFLAGS)
	
uniform_tree_test : uniform_tree_test.o
	$(CC) $< $(OBJ) -o $@ $(LDFLAGS)

clean:
	rm *.o $(PROGS)
