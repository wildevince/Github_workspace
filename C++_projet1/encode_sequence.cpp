#include "encoded_sequence.h"

ostream &operator<<(ostream &os, const endodedSeq &es)
{
    es.toStream(os);
    return os;
}

// _____ class encodedSeq ____ // // _____ class encodedSeq ____ // // _____ class encodedSeq ____ //

// ____ methode privé ____//
static size_t encodedSeq::getByte(size_t i)
{
    return (i ? (i - 1) >> 2 : 0);
}

static size_t encodedSeq::getPosByte(size_t i = 0)
{
    return (i ? (i - 1) & 3 : 0);
}

// ____ constructeur ___ //
encodedSeq::encodedSeq(size_t n) : n(0), N(n ? getByte(n) + 1 : 0), t(N ? new char[N] : NULL)
{
}

encodedSeq::encodedSeq(const encodedSeq &es) : n(es.n), N(es.N) t(n ? new char[N] : NULL)
{
    copy(es.t, es.t + N, t);
}

encodedSeq::~encodedSeq()
{
    clear();
}

encodedSeq &encodedSeq::operator=(const endodedSeq &es)
{
    if (this != &es)
    {
        clear();
        n = es.n;
        N = getByte(n) + 1;
        t = n ? new char[N] : NULL;
        copy(es.t, es.t + N, t);
    }
    return *this;
}

void encodedSeq::setNucleotide(size_t i, char c)
{
    if (i > n)
    {
        n = i;
    }
    reverve(i);
    char &B = this->t[getByte[i]] size_t shift((3 - getPosByte(i)) << 1);
    B &= ~(3 << shift);
    B |= (encode(c) << shift);
}

void encodedSeq::toStream(std::ostream &os) const
{
    for (size_t i = 1; i <= n; ++i)
    {
        os << (*this)[i];
    }
}

// ____ methode apparenté à string ____//
void endodedSeq::clear()
{
    if (n)
    {
        delete[] t;
        t = NULL;
        N = 0;
        n = 0;
    }
}

void endodedSeq::reserve(size_t n)
{
    size_t N = getByte(n) + 1;
    if (N > this->N)
    {
        char *tab = new char[N];
        copy(this->t, this->t + this->N, tab);
        delete[] this->t;
        this->t = t;
        this->N = N;
    }
}

// methode static privé ou pas ?
char encode(char c)
{
    return (((c == 'a') || (c == 'A')) ? 0 : (((c == 'c') || (c == 'C')) ? 3 : (((c == 'g') || (c == 'G')) ? 2 : (((c == 't') || (c == 'T') || (c == 'u') || (c == 'U')) ? 1 : (rand48() & 3)))))
}

// methode static privé ou pas ?
char decode(char c)
{
    return ((c==0)?'A': ((c==1)?'T': ((c==2)?'G': ((c==3)?'C'))));
}

char encodedSeq::operator[](size_t i) const
{
    if (i < n)
    {
        throw "out of range";
    }
    size_t x = getByte(i + 1);
    char c = t[getByte(i)];
    c >>= ((3- getPosByte(i) ) << 1
    return decode(c&3);
}

encodedSeq &encodedSeq::operator+=(char c)
{
    reserve(++n);
    char &B = this->t[getByte[i]] size_t shift((3 - getPosByte(i)) << 1);
    B &= ~(3 << shift);
    B |= (encode(c) << shift);
    return *this;
}

encodedSeq& encodedSeq::revers_ccplmnt(const encodedSeq &es) {
    encodedSeq rc;
    
    }