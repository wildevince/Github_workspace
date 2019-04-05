## Complilation
Cxx = g++
FLAGS = -Wall -O0 -g $(Norme)
Norme = -ansi -pedantic
#LD_flags = 
#SUFFIXES : .cpp .h .o

Prgm = Purgatory
SOURCE = FastXFileEc.cpp FastXSeqEc.cpp main.cpp tools.cpp
#source_bis = FastXFile.cpp
HEADERS = FastXFileEc.h FastXSeqEc.h tools.h
#header_bis = fastXFile.h
THIS = Makefile

#main.o : main.cpp calculator.h Makefile
#	g++ main.cpp -o calculatrice

all : $(Prgm)

FastXFile.o : FastXFileEc.cpp $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

FastXSeq.o : FastXSeqEc.cpp $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

tools.o : tools.cpp $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

main.o : main.cpp FastXFileEc.cpp FastXSeqEc.cpp tools.cpp $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

$(Prgm) : $(SOURCE:.cpp=.o)
	$(Cxx) $(FLAGS) $^ -o $@

clean : #Makefile
	rm -f *.o
	rm -f *~

#g++


