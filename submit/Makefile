CXXFLAGS=-std=c++14
HEADERS=project3.h utils.h graph.h node.h tests.h
SOURCES= \
	main.cpp\
	graph.cpp\
	node.cpp\
	erdos_renyi.cpp\
	graph_algorithms.cpp\
	utils.cpp

proj2: $(HEADERS) $(SOURCES)
	g++ $(CXXFLAGS) $(SOURCES) -o proj3

clean:
	rm -rf proj3 *.csv
