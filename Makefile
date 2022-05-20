# simple raytracer
# based on the book "The Ray Tracer Challenge" by Jamis Buck

CXXFLAGS = -std=c++14 -ggdb3 -Wall

raytracer:         main.o tests.o film.o matrix.o util.o ray.o intersections.o
	g++ -o raytracer main.o tests.o film.o matrix.o util.o ray.o intersections.o

main.o: main.cpp tests.h 
	g++ $(CXXFLAGS) -c main.cpp

tests.o: tests.cpp tests.h point.h vector.h color.h film.h matrix.h util.h ray.h sphere.h intersections.h
	g++ $(CXXFLAGS) -c tests.cpp

film.o: film.cpp film.h color.h
	g++ $(CXXFLAGS) -c film.cpp

matrix.o: matrix.cpp matrix.h point.h vector.h util.h
	g++ $(CXXFLAGS) -c matrix.cpp

ray.o: ray.cpp ray.h point.h vector.h matrix.h
	g++ $(CXXFLAGS) -c ray.cpp

util.o: util.cpp util.h
	g++ $(CXXFLAGS) -c util.cpp

intersections.o:  intersections.cpp intersections.h ray.h sphere.h util.h
	g++ $(CXXFLAGS) -c intersections.cpp

.PHONY: clean
clean:
	rm -f *.o raytracer

