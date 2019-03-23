## Complilation
Cxx = g++
Norme = -ansi -pedantic
FLAGS = -Wall -O0 -g $(Norme)
#LD_flags = 
#SUFFIXES : .cpp .h .o

Prgm = Purgatory
SOURCE = FastXSeqEc.cpp FastXFileEc.cpp tools.cpp main.cpp
#source_bis = FastXFile.cpp
HEADERS = FastXSeqEc.h FastXFileEc.h tools.h
#header_bis = fastXFile.h
THIS = Makefile

all : $(Prgm)

FastXSeqEc.o : FastXSeqEc.cpp $(THIS) FastXSeqEc.h tools.h
	$(Cxx) -c $(FLAGS) $<

FastXFileEc.o : FastXFileEc.cpp $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

tools.o : tools.cpp tools.h $(THIS)
	$(Cxx) -c $(FLAGS) $<

main.o : main.cpp FastXSeqEc.cpp FastXFileEc.cpp tools.cpp $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

$(Prgm) : $(SOURCE:.cpp=.o)
	$(Cxx) $(FLAGS) $^ -o $@

clean : #Makefile
	rm -f *.o
	rm -f *~

#