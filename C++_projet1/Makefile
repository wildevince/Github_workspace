## Complilation
Cxx = g++
FLAGS = -Wall -O0 -g $(Norme)
Norme = -ansi -pedantic
#LD_flags = 
#SUFFIXES : .cpp .h .o

Prgm = Purgatory
SOURCE = FastXSeq.cpp FastXFile.cpp
#source_bis = FastXFile.cpp
HEADERS = FastXSeq.h FastXFile.h tools.h
#header_bis = fastXFile.h
THIS = Makefile

#main.o : main.cpp calculator.h Makefile
#	g++ main.cpp -o calculatrice

all : $(Prgm)

FastXSeq.o : FastXSeq.cpp $(THIS) FastXSeq.h tools.h
	$(Cxx) -c $(FLAGS) $<

FastXFile.o : FastXFile.cpp $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

#tools.o : tools.cpp tools.h $(THIS)
#	$(Cxx) -c $(FLAGS) $<

main.o : main.cpp $(SOURCE) $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

$(Prgm) : $(SOURCE:.cpp=.o)
	$(Cxx) $(FLAGS) $^ -o $@

clean : #Makefile
	rm -f *.o
	rm -f *~

#