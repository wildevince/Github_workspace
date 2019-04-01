#ifndef __ECS_H__
#define __ECS_H__

#include <fstream>
#include <cstring>
#include <stddef.h>
#include <iostream>

/*
    alert
 manques les imports
 et encode et decode 
 getNucleotide() 

 */

/* codage :
 A  = 00  (0)        
T/U = 01  (1)
 G  = 10  (2)
 C  = 11  (3)
*/

class EncodedSeq
{
  private:
    size_t n, N;  // n = taille courante,  N = taille total allouée
    char *tabseq; // sequence
    static size_t getByte(size_t i);
    static size_t getPosInByte(size_t i = 0);

  public:
    //EncodedSeq();
    EncodedSeq(size_t n = 0);
    EncodedSeq(const EncodedSeq &es);
    ~EncodedSeq();
    EncodedSeq &operator=(const EncodedSeq &es); // methode applée quand j'instancie EncodedSeq dans parseq

    char getNucleotide(size_t i) const; // en comptant à partir de 1
    size_t size() const;
    void setNucleotide(size_t i, char c); // en comptant à partir de 1
    void clear();
    void reserve(size_t n);
    void toStream(std::ostream &os) const;
    char operator[](size_t i) const; // en comptant à partir de 1
    EncodedSeq &operator+=(char c);
    //EncodedSeq &operator+= (EncodedSeq &aES);
    EncodedSeq &operator+=(const std::string sp);

    // revers_ccplmnt
    // operator (ou exclusif)
    // EncodedSeq subseq( size_t start, siret_t l= (size_t) -1) const
    // EncodedSeq operator() (size_t start, siret_t l= (size_t) -1) const
};

std::ostream &operator<<(std::ostream &os, const EncodedSeq &es);
char encode(char c);
char decode(char ec);

/* size_t graine = (getpid()*time(NULL)); // pour le debogger
// srand48(getpid()*time(NULL)); */

#endif