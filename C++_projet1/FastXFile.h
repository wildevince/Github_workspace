#ifndef __FXF_H__
#define __FXF_H__

#include <ostream>
#include "FastXSeq"

class FastXFile {
    private:
        const char*  fileName;
        size_t *pos; 
        size_t nb_sequence;
        //table des sequenceX /fasta /fastQ
        void parse();

    public:
        // constructor
        FastXFile(const char* f = NULL);
        FastXFile(const FastXFile &f); //constructor par copie
        //destuctor
        ~FastXFile();
        // operator=
        FastXFile& operator=(const FastXFile &f); 
        FastXSeq operator[](size_t i) const; // getSequence

        //accesseur en lecture  getters
        size_t getNbSequence() const ;
        const char* getFileName() const;
        FastXSeq getSequence(size_t i) const;

        //accesseur d'écriture  setters
        void setFileName(const char* f); 

        // display par flux de sorti
        void toStream(ostream &os) const;

        
};

ostream &operator<<(ostream &os, const FastXFile &f);

#endif