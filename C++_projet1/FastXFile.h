#ifndef __FXF_H__
#define __FXF_H__

#include <iostream>
#include "FastXSeq.h" 

//class FastXSeq ; 

/* FastXfile: Verifie le format, teste l'intégrité du ficher, compte le nbr de 
sequences et donne la position.
Methodes /* parse() : méthode qui permet de lire le fichier, vérifie le format,
recupère la position de la séquence. 


   */

class FastXFile {
    private:
        char*  fileName;// Pointeur sur une chaine caracteres correspondant au nom du fichier
        size_t *pos; // Pointeur sur la position du début de la séquence
        FastXSeq *list_seq; // Pointeur vers un objet FastXSeq 
        size_t nb_sequence; // Entier correspondant au nombre de séquences
        //table des XSeq /fasta /fastQ
        void parse(); 


        //FastXSeq::FastXSeq XSeq;

    public:
        // constructor
        FastXFile(char* f = NULL);
        FastXFile(const FastXFile &f); //constructor par copie
        //destuctor
        ~FastXFile();
        // operator=
        FastXFile& operator=(const FastXFile &f); 
        FastXSeq& operator[](size_t i) ; // getSequence

        //accesseur en lecture  getters
        size_t getNbSequence() const ;
        char* getFileName() const;
        //FastXSeq getSequence(size_t i) const;

        //accesseur d'écriture  setters
        void setFileName(char* f); 

        // display par flux de sorti
        void toStream(std::ostream &os) const;

        
};

std::ostream &operator<<(std::ostream &os, const FastXFile &f);

#endif