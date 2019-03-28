#include "encoded_sequence.h"
#include "random" 
#include <iostream>
#include <fstream>
#include <cstring>
#include <stddef.h>

using namespace std;

ostream &operator<<(ostream &os, const EncodedSeq &es)
{
    es.toStream(os);
    return os;
}

// _____ class EncodedSeq ____ // // _____ class EncodedSeq ____ // // _____ class EncodedSeq ____ //

EncodedSeq::EncodedSeq(size_t n) : n(0), N(n ? getByte(n) + 1 : 0), tabseq(N ? new char[N] : NULL)
{
}

EncodedSeq::EncodedSeq(const EncodedSeq &es) : n(es.n), N(es.N), tabseq(n ? new char[N] : NULL)
{
    copy(es.tabseq, es.tabseq + N, tabseq);
}

EncodedSeq::~EncodedSeq()
{
    clear();
}

EncodedSeq &EncodedSeq::operator=(const EncodedSeq &es)
{
    if (this != &es)
    {
        clear();
        n = es.n;
        N = getByte(n) + 1;
        tabseq = (n ? new char[N] : NULL);
        copy(es.tabseq, es.tabseq + N, tabseq);
    }
    return *this;
}

void EncodedSeq::clear()
{
    if (n)
    {
        delete[] tabseq;
        tabseq = NULL;
        N = 0;
        n = 0;
    }
}
void EncodedSeq::reserve(size_t n)
{
        size_t M = getByte(n) + 1;
        if (M > this->N)
        {
            char *tab = new char[M]; // new tab de char de la bonne taille !
            copy(this->tabseq, this->tabseq + this->N, tab);
            delete[] this->tabseq;
            this->tabseq = tab;
            this->N = M;
        }
}

size_t EncodedSeq::getByte(size_t i)
    {                                  // en comptant à partir de 1 ( d'ou le 'i-1' )
        return (i ? (i - 1) >> 2 : 0); // on a diviser i-1 par 4 ! on a donc le nombre d'octet
    }

size_t EncodedSeq::getPosInByte(size_t i)
    {                                 // la position dans l'octet
        return (i ? (i - 1) & 3 : 0); //  =  modulo par 4 (%4) : soit 0, 1, 2, 3
        /* '&' = et binaire
       00 01 01 01  (= 21 /²)
  & __00_00_00_11__ (=  3 /²)
       00 00 00 01  (= 1 soit le 2e position)*/
    }

    // a placer
    // methode static privé ou pas ?
    char encode(char c)
    {
        return (((c == 'a') || (c == 'A'))
                ? 0
                  : (((c == 'c') || (c == 'C'))
                     ? 3
                       : (((c == 'g') || (c == 'G'))
                          ? 2
                            : (((c == 't') || (c == 'T') || (c == 'u') || (c == 'U'))
                               ? 1
                                 : (mrand48() & 3)))));
    }

    // a placer
    // methode static privé ou pas ?
    char decode(char ec)
    {
    return ((ec==0)?'A'
            : ((ec==1)
               ?'T'
               : ((ec==2)
                  ?'G'
                  :'C')));
                  //: ((ec==3)?'C'))));
    }

    //corected
    char EncodedSeq::operator[](size_t i) const
    { // en comptant à partir de 1
      try
        {
          if (i < n)
            {
              throw "out of range";
            }
        }
      catch(const char* exception)
        {
          cerr << exception << endl;
        }
        //size_t x = getByte(i+1);
        char c = tabseq[getByte(i)]; // je veux le caractere dans l'octet n° i
        c >>= ((3 - getPosInByte(i)) << 1);
        return decode(c & 3);
    }

    void EncodedSeq::setNucleotide(size_t i, char c)
    {
      try
        {
          if (i > N)
            {
            throw "Out of range";
            }
        }
      catch(const char* exception)
        {
          cerr << exception << endl;
        }
      reserve(i);
      if (i > n)
        {
            n = i;
        }
      //<<<<<<< HEAD
      //char B = this->tabseq[getByte(i)]; // B = adress du char
      //size_t shift = ((3 - getPosInByte(i)) << 1); // décalage en fct de la position du char dans l'octet
        //=======
        reserve(i); 
        char &B = this->tabseq[getByte(i)]; // B = adress du char
        size_t shift((3 - getPosInByte(i)) << 1); // décalage en fct de la position du char dans l'octet
        //>>>>>>> bb9a195b87981550c346358b8b46f17221718a56
        B &= ~(3 << shift); // on a supp le char précedent mais en gardant les autres 
        // puis encode(c) = la version encodee du new char à ecrire
        B |= (encode(c) << shift); // on le place donc au bon endroit
    }

    char EncodedSeq::getNucleotide(size_t i) const {
        size_t shift = ((3-getPosInByte(i)) << 1) ;
        char byte = tabseq[getByte(i)] ;
        byte &= (3 << shift) ;
        return (decode(byte)) ;
    }
    
    void EncodedSeq::toStream(std::ostream & os) const
    {
        for (size_t i = 1; i <= n; ++i)
        {
            os << (*this)[i]; // appel de EncodedSeq::operator[]
        }
    }

    // modified
    EncodedSeq &EncodedSeq::operator+=(char c) 
    { // = pushback
        reserve(++n);
        char &B = this->tabseq[getByte(n)] ; // le dernier ?
        size_t shift = ((3 - getPosInByte(n)) << 1);
        B &= ~(3 << shift);
        B |= (encode(c) << shift);
        return *this; 
    }
