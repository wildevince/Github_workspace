#ifndef __FXF_H__
#define __FXF_H__


#include <string>
//#include "FastXSeq.h" 

class FastXFile {
private:
	const char*  fileName;
	size_t *pos; //Pointeur nombre e case sera �gale au nombre de seq pointeur de pointeur
	size_t nb_sequence;
	//table des sequenceX /fasta /fastQ
	void parse(); // cotrole et maitrise de la m�thode car elle cr�e les objets

public:
	// constructor
	FastXFile(const char* f = NULL);// f nom du fichier
	FastXFile(const FastXFile &f); //constructor par copie par ref
	//destuctor
	~FastXFile();
	// operator=
	FastXFile& operator=(const FastXFile &f);
	//FastXSeq operator[](size_t i) const; // getSequence

	//accesseur en lecture  getters
	size_t getNbSequence() const;
	const char* getFileName() const;
	FastXSeq getSequence(size_t i) const; //r�cup�re une seq � une position donn�e dans le tab

	//accesseur d'�criture  setters
	void setFileName(const char* f);

	// display par flux de sorti
	void toStream(ostream &os) const;


};

ostream &operator<<(ostream &os, const FastXFile &f);
const char* myStrDup(const char* s);
bool ifspace(char c, bool newline);

#endif