#ifndef __FXF_H__
#define __FXF_H__


//#include "FastXSeq.h" 
#include"FastXSeqEc.h"
#include <iostream>
#include <stddef.h>
#include <string>

//class FastXSeq; 

class FastXFile {
private:
	char*  fileName;
	size_t *pos;
	size_t nb_sequence;
	//table des XSeq /fasta /fastQ
	void parse();
	//FastXSeq::FastXSeq XSeq;

public:

	// référence à la classe FastXSeq 
	FastXSeq *list_seq;

	// constructor
	FastXFile(char* f = NULL);
	FastXFile(const FastXFile &f); //constructor par copie
	//destuctor
	~FastXFile();
	// operator=
	FastXFile& operator=(const FastXFile &f);
	FastXSeq& operator[](size_t i); // getSequence

	//accesseur en lecture  getters
	size_t getNbSequence() const;
	char* getFileName() const;
	//FastXSeq& getSequence(size_t i) const;

	//accesseur d'écriture  setters
	void setFileName(char* f);

	// display par flux de sorti
	void toStream(std::ostream &os) const;


};

std::ostream &operator<<(std::ostream &os, const FastXFile &f);



#endif