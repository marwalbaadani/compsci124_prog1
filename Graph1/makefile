mst: graph1_22.o graph1_utils.o
	g++ graph1_22.o graph1_utils.o -o mst -std=c++11

graph1_22.o: graph1_22.cpp
	g++ -c graph1_22.cpp -std=c++11

graph1_utils.o: graph1_utils.cpp
	g++ -c graph1_utils.cpp  -std=c++11


clean:
	rm *.o mst