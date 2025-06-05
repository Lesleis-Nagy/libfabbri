all: linalg-sources linalg-build

linalg-sources:
	rm -f linalg-tests
	python gen-linalg-vector.py > linalg_vector.hpp
	python gen-linalg-vector-tests.py > linalg_vector_tests.cpp

linalg-build:
	g++ -std=c++20 linalg_vector_tests.cpp -I /Users/lnagy2/Projects/libfabbri/third-party/catch2-v2.13.9/include -I /opt/homebrew/include -I /Users/lnagy2/Projects/libfabbri/third-party/mpreal-v3.7.0/include /opt/homebrew/lib/libmpfr.dylib -o linalg-vector-tests

clean:
	rm -f *.hpp
	rm -f *.cpp
	rm -f *linalg-vector-tests

