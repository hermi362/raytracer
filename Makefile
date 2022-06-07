# simple raytracer
# based on the book "The Ray Tracer Challenge" by Jamis Buck

# debug build
CXXFLAGS = -std=c++14 -ggdb3 -Wall

#release build
#CXXFLAGS = -std=c++14 -O3 -Wall

raytracer:         main.o tests.o film.o matrix.o util.o ray.o sphere.o scene.o
	g++ -o raytracer main.o tests.o film.o matrix.o util.o ray.o sphere.o scene.o

main.o: main.cpp   tests.h point.h vector.h color.h film.h matrix.h util.h ray.h sphere.h material.h light.h scene.h
	g++ $(CXXFLAGS) -c main.cpp

tests.o: tests.cpp tests.h point.h vector.h color.h film.h matrix.h util.h ray.h sphere.h material.h light.h scene.h
	g++ $(CXXFLAGS) -c tests.cpp

film.o: film.cpp film.h color.h
	g++ $(CXXFLAGS) -c film.cpp

matrix.o: matrix.cpp matrix.h point.h vector.h util.h
	g++ $(CXXFLAGS) -c matrix.cpp

ray.o: ray.cpp ray.h point.h vector.h matrix.h light.h material.h
	g++ $(CXXFLAGS) -c ray.cpp

util.o: util.cpp util.h
	g++ $(CXXFLAGS) -c util.cpp

sphere.o: sphere.cpp sphere.h ray.h shape.h
	g++ $(CXXFLAGS) -c sphere.cpp

scene.o: scene.cpp scene.h light.h sphere.h
	g++ $(CXXFLAGS) -c scene.cpp


.PHONY: clean
clean:
	rm -f *.o raytracer

