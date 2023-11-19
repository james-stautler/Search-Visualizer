CC = g++
CFLAGS = -I/opt/homebrew/Cellar/sfml/2.6.0/include -L/opt/homebrew/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system -w

main: main.o tile.o button.o tileCollection.o
	$(CC) $(CFLAGS) -o search main.o tile.o button.o tileCollection.o

main.o: main.cpp tile.o button.o tileCollection.o
	$(CC) $(CFLAGS) -c main.cpp

tileCollection.o: tile.o tileCollection.cpp
	$(CC) $(CFLAGS) -c tileCollection.cpp

tile.o: tile.cpp
	$(CC) $(CFLAGS) -c tile.cpp

button.o: button.cpp
	$(CC) $(CFLAGS) -c button.cpp


clean:
	rm -r *.o search