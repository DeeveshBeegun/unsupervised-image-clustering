CC=g++
LIBS = -std=c++11
LIB = ./lib
DIR = ./src

clusterer: Clusterer.o Classification.o
	$(CC) -o clusterer $(DIR)/Clusterer.cpp $(DIR)/Classification.cpp $(LIBS)

Clusterer.o: $(DIR)/Clusterer.cpp $(DIR)/Clusterer.h
	$(CC) -c -o $(DIR)/Clusterer.o $(DIR)/Clusterer.cpp $(LIBS)

Classification.o: $(DIR)/Classification.cpp $(DIR)/Classification.h
	$(CC) -c -o $(DIR)/Classification.o $(DIR)/Classification.cpp $(LIBS)

run:
	export LD_LIBRARY_PATH = ./clusterer

clean:
	@rm $(DIR)/*.o
	@rm ./clusterer