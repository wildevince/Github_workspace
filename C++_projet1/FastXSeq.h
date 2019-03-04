#ifndef __FXS_H__
#define __FXS_H__

#include "FastXFile.h"
#include "encoded_sequence.h"

class FastXSeq {
    private:
        const char* header;
        string sequence;
        //encodedSeq* sequence;
    //
    public:
        FastXSeq(const char* head = NULL, string es = "");
        //FastXSeq(const char* head = NULL, EncodedSeq* es = NULL);
        FastXSeq(const FastXSeq& fx);
        ~FastXSeq();
        //
        FastXSeq& operator=(const FastXSeq& fx);
        string operator[](size_t i) const;
        //encodedSeq operator[](size_t i) const;
        //
        const char* getHeader() const;
        string getSequence() const;
        //encodedSeq& getSequence() const;
        //
        void setHeader(char* head);
        //
        void toStream(std::ostream &os) const;
        void parseq(ifstream& ifs); 

    //
};

std::ostream& operator<< (std::ostream &os, const FastXseq& fx);

#endif