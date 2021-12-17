# simple raytracer
# based on the book "The Ray Tracer Challenge" by Jamis Buck

CXXFLAGS = -std=c++14 -ggdb3 -Wall

raytracer:         main.o tests.o canvas.o matrix.o util.o
	g++ -o raytracer main.o tests.o canvas.o matrix.o util.o

main.o: main.cpp tuple.h color.h tests.h canvas.h
	g++ $(CXXFLAGS) -c main.cpp

tests.o: tests.cpp tuple.h color.h tests.h canvas.h matrix.h util.h
	g++ $(CXXFLAGS) -c tests.cpp

canvas.o: canvas.cpp canvas.h color.h
	g++ $(CXXFLAGS) -c canvas.cpp

matrix.o: matrix.cpp matrix.h tuple.h util.h
	g++ $(CXXFLAGS) -c matrix.cpp

util.o: util.cpp util.h
	g++ $(CXXFLAGS) -c util.cpp

.PHONY: clean
clean:
	rm *.o raytracer

