## Complilation
Cxx = g++
Norme = -ansi -pedantic
FLAGS = -Wall -O0 -g $(Norme)
#LD_flags = 
#SUFFIXES : .cpp .h .o

Prgm = Purgatory
SOURCE = FastXSeq.cpp FastXFile.cpp main.cpp
#source_bis = FastXFile.cpp
HEADERS = FastXSeq.h FastXFile.h tools.h
#header_bis = fastXFile.h
THIS = Makefile

all : $(Prgm)

FastXSeq.o : FastXSeq.cpp $(THIS) FastXSeq.h tools.h
	$(Cxx) -c $(FLAGS) $<

FastXFile.o : FastXFile.cpp $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

#tools.o : tools.cpp tools.h $(THIS)
#	$(Cxx) -c $(FLAGS) $<


main.o : main.cpp FastXSeq.cpp FastXFile.cpp $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

$(Prgm) : $(SOURCE:.cpp=.o)
	$(Cxx) $(FLAGS) $^ -o $@

clean : #Makefile
	rm -f *.o
	rm -f *~

#