OBJ = compito.o grafi.o
CXXFLAGS=-Wall

Web-graph: $(OBJ)
	g++ -o Web-graph $(OBJ)

-include dependencies

.PHONY: clean cleanall run
depend:
	g++ -MM *.cpp > dependencies
clean:
	rm -f *.o
cleanall:
	rm -f Web-graph *.o