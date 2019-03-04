## Complilation
Cxx = g++
FLAGS = -Wall -O0 -g
Norme = -ansi -pedantic
#LD_flags = 
#SUFFIXES : .cpp .h .o

Prgm = albanrithmetic
SOURCE = FastXFile.cpp main.cpp
#source_bis = FastXFile.cpp
HEADERS = FastXFile.h
#header_bis = fastXFile.h
THIS = Makefile

#main.o : main.cpp calculator.h Makefile
#	g++ main.cpp -o calculatrice

FastXFile.o : $(SOURCE) $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

(Prgm) : $(SOURCE:.cpp=.o)
	$(Cxx) $(FLAGS) $^ -o $@

clean : #Makefile
	rm -f *.o
	rm -f *~

#g++ 