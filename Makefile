CC=gcc
CFLAGS=`pkg-config --cflags gtk+-2.0 opencv` -g 
LDFLAGS=`pkg-config --libs gtk+-2.0 opencv` -lm -lgmp

OBJ=main.o ui.o ui_action.o menu_bar.o game.o graph.o random.o experiment.o colourmap.o

%.o : %.c
	$(CC) -c $< $(CFLAGS) -o $@
	
simulator: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o simulator

clean:
	rm *.o simulator
