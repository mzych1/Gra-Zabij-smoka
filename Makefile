debug: *.cpp *.h
		g++ -g -O0 -o debug *.cpp
release: *.cpp *.h
		g++  -O2 -o release *.cpp
