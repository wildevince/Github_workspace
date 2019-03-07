## Complilation
Cxx = g++
FLAGS = -Wall -O0 -g $(Norme)
Norme = -ansi -pedantic
#LD_flags = 
#SUFFIXES : .cpp .h .o

Prgm = Purgatory
SOURCE = FastXFile.cpp FastXSeq.cpp main.cpp
#source_bis = FastXFile.cpp
HEADERS = FastXFile.h FastXSeq.h
#header_bis = fastXFile.h
THIS = Makefile

#main.o : main.cpp calculator.h Makefile
#	g++ main.cpp -o calculatrice

all : $(Prgm)

FastXFile.o : FastXFile.cpp $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

FastXSeq.o : FastXSeq.cpp $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

main.o : main.cpp FastXFile.cpp FastXSeq.cpp $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

$(Prgm) : $(SOURCE:.cpp=.o)
	$(Cxx) $(FLAGS) $^ -o $@

clean : #Makefile
	rm -f *.o
	rm -f *~

#g++