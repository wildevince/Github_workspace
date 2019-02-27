## Complilation
Cxx = g++
FLAGS = -Wall -ansi -pedantic -O0 -g
#LD_flags = 
#SUFFIXES : .cpp .h .o

Prgm = albanrithmetic
SOURCE = FastXFile.cpp 
HEADERS = FastXFile.h
THIS = Makefile

#main.o : main.cpp calculator.h Makefile
#	g++ main.cpp -o calculatrice

FastXFile.o : FastXFile.cpp $(THIS) FastXFile.h
	$(Cxx) -c $(FLAGS) $<

(Prgm) : $(SOURCE:.cpp=.o)
	$(Cxx) $(FLAGS) $^ -o $@

clean : #Makefile
	rm -f *.o
	rm -f *~
