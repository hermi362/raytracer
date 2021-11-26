# simple raytracer
# based on the book "The Ray Tracer Challenge" by Jamis Buck

raytracer:         main.o tests.o canvas.o matrix.o util.o
	g++ -o raytracer main.o tests.o canvas.o matrix.o util.o

main.o: main.cpp tuple.h color.h tests.h canvas.h
	g++ -Wall -c main.cpp

tests.o: tests.cpp tuple.h color.h tests.h canvas.h matrix.h util.h
	g++ -Wall -c tests.cpp

canvas.o: canvas.cpp canvas.h color.h
	g++ -Wall -c canvas.cpp

matrix.o: matrix.cpp matrix.h tuple.h util.h
	g++ -Wall -c matrix.cpp

util.o: util.h

clean:
	rm *.o raytracer

