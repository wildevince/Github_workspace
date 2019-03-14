#ifndef __AI_H__
#define __AI_H__

#include <iostream>
#include <fstream>
#include <cstring>
#include <stddef.h>
#include <string>
#include <algorithm>

//#include "encoded_sequence.h"

class FastXSeq {
    private:
        char* header;
        size_t start_seq; // position dans fichier
        size_t taille_seq;
        //
        std::string sequence;
        //encodedSeq sequence;
        //FastXSeq *l_xseq;
        //FastXFile fichier;
        
    //
    public:
        FastXSeq(char* head = NULL, size_t p = 0, size_t t = 0, std::string es = "");
        //FastXSeq(char* head = NULL, EncodedSeq* es = NULL);
        FastXSeq(const FastXSeq &fx);
        ~FastXSeq();
        //
        FastXSeq& operator=(const FastXSeq &fx);
        //std::string operator[](size_t i) const;
        //encodedSeq operator[](size_t i) const;
        //
        char* getHeader() const;
        std::string getSequence() const;
        size_t getStart() const;
        size_t getSize() const;
        //encodedSeq& getSequence() const;
        //
        void setHeader(char* head);
        void setHeader(std::string head);
        void setStart(size_t p);
        void setTaille(size_t t);
        //
        void toStream(std::ostream &os) const;
        void parseq(std::ifstream& ifs, size_t p); 

    //
};

std::ostream& operator<< (std::ostream &os, const FastXSeq& fx);


class FastXFile {
    private:
        char*  fileName;
        size_t *pos; 
        FastXSeq *list_seq;
        size_t nb_sequence;
        //table des XSeq /fasta /fastQ
        void parse();
        //FastXSeq::FastXSeq XSeq;

    public:
        // constructor
        FastXFile(char* f = NULL);
        FastXFile(const FastXFile &f); //constructor par copie
        //destuctor
        ~FastXFile();
        // operator=
        FastXFile& operator=(const FastXFile &f); 
        FastXSeq& operator[](size_t i) ; // getSequence

        //accesseur en lecture  getters
        size_t getNbSequence() const ;
        char* getFileName() const;
        //FastXSeq& getSequence(size_t i) const;

        //accesseur d'écriture  setters
        void setFileName(char* f); 

        // display par flux de sorti
        void toStream(std::ostream &os) const;

        
};

std::ostream &operator<<(std::ostream &os, const FastXFile &f);
char* myStrDup(char* s);
bool ifspace(char c ) ; // , bool newline) ;


#endif 