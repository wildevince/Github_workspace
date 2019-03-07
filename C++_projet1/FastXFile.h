#ifndef __FXF_H__
#define __FXF_H__

#include <iostream>
//#include "FastXSeq.h" 

class FastXFile {
    private:
        char*  fileName;
        size_t *pos; 
        size_t nb_sequence;
        //table des XSeq /fasta /fastQ
        void parse();

    public:
        // constructor
        FastXFile(char* f = NULL);
        FastXFile(const FastXFile &f); //constructor par copie
        //destuctor
        ~FastXFile();
        // operator=
        FastXFile& operator=(const FastXFile &f); 
        //FastXSeq operator[](size_t i) const; // getSequence

        //accesseur en lecture  getters
        size_t getNbSequence() const ;
        char* getFileName() const;
        //FastXSeq getSequence(size_t i) const;

        //accesseur d'écriture  setters
        void setFileName(char* f); 

        // display par flux de sorti
        void toStream(std::ostream &os) const;

        
};

std::ostream &operator<<(std::ostream &os, const FastXFile &f);
char* myStrDup(char* s);
bool ifspace(char c ) ; // , bool newline) ;

#endif