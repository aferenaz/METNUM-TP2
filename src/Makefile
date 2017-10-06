OBJS =  norma.o  knn.o pca.o metodoPotencia.o

%.o: %.cpp
	g++ -c -o $@ $^ -g

all: $(OBJS)
	g++ main.cpp $(OBJS) -o main -g

clean:
	rm -f *.o
	rm -f main