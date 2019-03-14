#ifndef __FXS_H__
#define __FXS_H__

//#include "FastXFile.h"
#include <cstring>
#include <stddef.h>
#include <fstream>
#include <iostream>

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
        void parseq(std::ifstream& ifs, std::string sp); 

    //
};

std::ostream& operator<< (std::ostream &os, const FastXSeq& fx);

#endif