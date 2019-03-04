#include "encoded_sequence.h"


// _____ class EncodedSeq ____ // // _____ class EncodedSeq ____ // // _____ class EncodedSeq ____ // 

ostream &operator<<(ostream &os, const EncodedSeq &es) {
    es.toStream(os);
    return os;
}


EncodedSeq::EncodedSeq(size_t n) : n(0), N(n? getByte(n)+1:0), t( N? new char[N]: NULL) {

}

EncodedSeq::EncodedSeq(const EncodedSeq &es) : n(es.n), N(es.N) t(n? new char[N]:NULL) {
    copy(es.t, es.t+N, t); 
}

EncodedSeq::~EncodedSeq() {
    clear();
}

EncodedSeq &EncodedSeq::operator=( const EncodedSeq &es ) {
    if (this != &es) {
        clear();
        n= es.n;
        N = getByte(n)+1;
        t = n? new char[N] : NULL ;
        copy(es.t, es.t+N, t);
    }
    return *this;
}

void EncodedSeq::clear() {
    if (n) {
    delete[] t;
    t = NULL;
    N = 0;
    n = 0;
}

void EncodedSeq::reserve(size_t n) {
    size_t N = getByte(n) +1;
    if (N > this->N) {
        char* tab = new char[N];
        copy(this->t, this->t+ this->N, tab);
        delete[] this->t;
        this->t = t;
        this->N = N;
    }
}

static size_t EncodedSeq::getByte(size_t i) {
    return (i? (i-1)>>2 : 0);
}

static size_t EncodedSeq::getPosByte(size_t i = 0) {
    return (i? (i-1)&3 : 0);
}

// methode static privé ou pas ?
char encode(char c) {
    return ((( c=='a')||(c=='A'))? 0: 
        (((c=='c')||(c=='C'))? 3:
            (((c=='g')||(c=='G'))? 2:
                (((c=='t')||(c=='T')||(c=='u')||(c=='U'))?1:
                    (rand48()&3) ))))
}

// methode static privé ou pas ?
char decode(char c) {
    return ((c==0)?'A': ((c==1)?'T': ((c==2)?'G': ((c==3)?'C')))); 
}

char EncodedSeq::operator[](size_t i) const {
    if (i<n) {
        throw "out of range";
    }
    size_t x = getByte(i+1);
    char c = t[getByte(i)];
    c >>= ((3- getPosByte(i) ) << 1
    return decode(c&3);
}

void EncodedSeq::setNucleotide(size_t i, char c){
    if (i > n ) {n = i;}
    reverve (i);
    char &B = this->t[getByte[i]]
    size_t shift ((3-getPosByte(i))<<1);
    B &= ~(3 << shift) ;
    B |= (encode(c) << shift);
    }

void EncodedSeq::toStream(std::ostream &os) const {
    for (size_t i = 1 ; i<= n ; ++i) {
    os << (*this)[i];}
}

EncodedSeq &EncodedSeq::operator+= (char c) {
    reserve (++n);
    char &B = this->t[getByte[i]]
    size_t shift ((3-getPosByte(i))<<1);
    B &= ~(3 << shift) ;
    B |= (encode(c) << shift);
    return *this;
}

