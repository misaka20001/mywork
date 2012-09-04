main: main.o Graph.o
	g++ -o $@ $^
main.o: main.cpp Graph.h
	g++ -c $<
Graph.o: Graph.cpp Graph.h
	g++ -c $<

clean:
	@echo "cleaning project"
	-rm main *.o
	@echo "cleaning completed"
