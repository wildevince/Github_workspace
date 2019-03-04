#ifndef __ECS_H__
#define __ECS_H__


class EncodedSeq {
    private:
        size_t n, N;
        char* t;
        static size_t getByte(size_t i);
        static size_t getPosByte(size_t i = 0);

    public:
        EncodedSeq();
        EncodedSeq(size_t n = 0);
        EncodedSeq(const EncodedSeq &es);
        ~EncodedSeq();
        EncodedSeq &operator=( const EncodedSeq &es );

        char getNucleotide(size_t i) const;
        void setNucleotide(size_t i, char c); 
        void clear();
        void reserve(size_t  n);
        void toStream(std::ostream &os) const;
        char operator[](size_t i) const;
        EncodedSeq &operator+= (char c);
        
        // revers_ccplmnt
        // operator (ou exclusif)
        // EncodedSeq subseq( size_t start, siret_t l= (size_t) -1) const
        // EncodedSeq operator() (size_t start, siret_t l= (size_t) -1) const
        )

};

std::ostream &operator<<(std::ostream &os, const EncodedSeq &es);

/* size_t graine = (getpid()*time(NULL)); // pour le debogger
// srand48(getpid()*time(NULL)); */


#endif