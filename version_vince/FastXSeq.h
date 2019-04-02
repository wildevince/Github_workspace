#ifndef __FXS_H__
#define __FXS_H__

//#include "FastXFile.h"
#include <cstring>
#include <stddef.h>
#include <iostream>
#include "encoded_sequence.h"

class FastXSeq
{
  private:
	char *header;
	size_t start_seq; // position dans fichier
	size_t taille_seq; // sert à rien 
	//
	//std::string sequence;
	EncodedSeq es;
	//FastXSeq *l_xseq;
	//FastXFile fichier;

	//
  public:
	FastXSeq(char *head = NULL, size_t p = 0, size_t t = 0, EncodedSeq *aes = NULL);
	//FastXSeq(char* head = NULL, EncodedSeq* es = NULL);
	FastXSeq(const FastXSeq &fx);
	~FastXSeq();
	//
	FastXSeq &operator=(const FastXSeq &fx);
	EncodedSeq &operator+=(const std::string sp);
	//std::string operator[](size_t i) const;
	char operator[](size_t i);
	//
	char *getHeader() const;
	const EncodedSeq& getSequence() const;
	size_t getStart() const;
	size_t getSize() const; // appel direct es.size(); 
	//encodedSeq& getSequence() const;
	//
	//void setSequence(std::string sp);
	//void setSequence(EncodedSeq &aes)
	void setHeader(char *head);
	void setHeader(std::string head);
	void setStart(size_t p);
	void setTaille(size_t t);
	//
	void toStream(std::ostream &os) const;
	void parseq(std::ifstream &ifs, std::string sp);	// Pour parser Fasta
	void parseqQ(std::ifstream &ifs, std::string line); // Pour parser Fastq

	//
};

std::ostream &operator<<(std::ostream &os, const FastXSeq &fx);

#endif