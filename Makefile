CC=g++
LIBS = -std=c++11
LIB = ./lib
DIR = ./src

clusterer: Clusterer.o Image.o DataPoints.o Classification.o 
	$(CC) -o clusterer $(DIR)/Image.cpp $(DIR)/Clusterer.cpp $(DIR)/DataPoints.cpp $(DIR)/Classification.cpp $(LIBS)

Clusterer.o: $(DIR)/Clusterer.cpp $(DIR)/Clusterer.h
	$(CC) -c -o $(DIR)/Clusterer.o $(DIR)/Clusterer.cpp $(LIBS)

Classification.o: $(DIR)/Classification.cpp $(DIR)/Classification.h
	$(CC) -c -o $(DIR)/Classification.o $(DIR)/Classification.cpp $(LIBS)

Image.o: $(DIR)/Image.cpp $(DIR)/Image.h
	$(CC) -c -o $(DIR)/Image.o $(DIR)/Image.cpp $(LIBS)

DataPoints.o: $(DIR)/DataPoints.cpp $(DIR)/DataPoints.h
	$(CC) -c -o $(DIR)/DataPoints.o $(DIR)/DataPoints.cpp $(LIBS)

run:
	export LD_LIBRARY_PATH = ./clusterer

clean:
	@rm $(DIR)/*.o
	@rm ./clusterer