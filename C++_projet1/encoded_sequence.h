#ifndef __ECS_H__
#define __ECS_H__


class endodedSeq {
    private:
        size_t n, N;
        char* t;
        static size_t getByte(size_t i);
        static size_t getPosByte(size_t i = 0);

    public:
        encodedSeq();
        encodedSeq(size_t n = 0);
        encodedSeq(const encodedSeq &es);
        ~encodedSeq();
        encodedSeq &operator=( const endodedSeq &es );

        char getNucleotide(size_t i) const;
        void setNucleotide(size_t i, char c); 
        void clear();
        void reserve(size_t  n);
        void toStream(std::ostream &os) const;
        char operator[](size_t i) const;
        encodedSeq &operator+= (char c);
        
        // revers_ccplmnt
        // operator (ou exclusif)
        // encodedSeq subseq( size_t start, siret_t l= (size_t) -1) const
        // encodedSeq operator() (size_t start, siret_t l= (size_t) -1) const
        )

}

std::ostream &operator<<(std::ostream &os, const encodedSeq &es);

/* size_t graine = (getpid()*time(NULL)); // pour le debogger
// srand48(getpid()*time(NULL)); */


#endif