CC=gcc
CFLAGS=`pkg-config --cflags gtk+-2.0 opencv` -g 
LDFLAGS=`pkg-config --libs gtk+-2.0 opencv` -lm -lgmp

OBJ=main.o ui.o uiactions.o menubar.o graph.o random.o

%.o : %.c
	$(CC) -c $< $(CFLAGS) -o $@
	
simulator: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o simulator

clean:
	rm *.o simulator
