## Complilation
Cxx = g++
Norme = -ansi -pedantic
FLAGS = -Wall -O1 -g $(Norme)
#LD_flags = 
#SUFFIXES : .cpp .h .o

Prgm = Purgatory
SOURCE = FastXSeq.cpp FastXFile.cpp tools.cpp main.cpp encode_sequence.cpp
#source_bis = FastXFile.cpp
HEADERS = FastXSeq.h FastXFile.h tools.h encoded_sequence.h
#header_bis = fastXFile.h
THIS = Makefile

all : $(Prgm)

encode_sequence.o : encode_sequence.cpp $(THIS) encoded_sequence.h
	$(Cxx) -c $(FLAGS) $<

FastXSeq.o : FastXSeq.cpp $(THIS) FastXSeq.h tools.h
	$(Cxx) -c $(FLAGS) $<

FastXFile.o : FastXFile.cpp $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

tools.o : tools.cpp tools.h $(THIS)
	$(Cxx) -c $(FLAGS) $<

main.o : main.cpp FastXSeq.cpp FastXFile.cpp tools.cpp $(THIS) $(HEADERS)
	$(Cxx) -c $(FLAGS) $<

$(Prgm) : $(SOURCE:.cpp=.o)
	$(Cxx) $(FLAGS) $^ -o $@

clean : #Makefile
	rm -f *.o
	rm -f *~

#